#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "ll.h"
#include "parser.h"
#include "expression.h"
#include "operator.h"
#include "object.h"
#include "umbrella_interpreter.h"
#include "umbrella_ast_transform.h"//TODO: consider not placing private headers in the source folder.  Idk it's just an idea.

//um_transform* functions generally should construct some umbrella specific
//struct from an ast for source code and return with the ast node they were
//given deleted.  This might be a bad idea, but right now it seems like a
//good one.

void um_transform_ast(block *out, ast *r){
	return um_transform_block(out, r);
}

void um_transform_block(block *out, ast *r){
	//block= label_tag? whitespace? lbracket statement* whitespace? rbracket
	//statement= label_tag? bare_statement whitespace? semicolon
	//bare_statement= (expr whitespace? comma)* expr?
	//label_tag= whitespace? identifier whitespace? colon colon whitespace?
	*out = (block){0};
	ast *label = r->size ? r->children[0] : NULL;
	if(!strcmp("label_tag", label->name)){
		out->tag_len = label->length;
		out->tag = malloc(out->tag_len + 1);
		memcpy(out->tag, label->text, out->tag_len + 1);
		delete_ast(label);
	}else{
		label = NULL;
	}
	for(size_t i = !!label; i < r->size; ++i){//loop over all of the statements once to count them
		ast *statement = r->children[i];
		if(statement->size == 2){
			out->len += statement->children[1]->size + 1;
		}else{
			out->len += statement->children[0]->size;
		}
	}
	out->statements = malloc(out->len*sizeof(expression));
	for(size_t i = !!label, j = 0; i < r->size; ++i){
		ast *statement = r->children[i];
		if(statement->size == 2){
			out->statements[j] = (expression){.op=OP_ID, .len=0};
			avl_node_char__expression_ label = {
				.key=strdup(statement->children[0]->text),
				.val=out->statements + j,
			};
			avl_insert(&out->labels, &label, &avl_ft_char__expression_);
			++j;
			statement = statement->children[1];
		}else{
			statement = statement->children[0];
		}
		for(size_t i = 0; i < statement->size; ++i){//this is not the i from the outer loop
			ast *expr = statement->children[i];
			um_transform_expr(out->statements + j, expr);
			out->statements[j].assign_undesignated = statement->size > 1;//note I kind of want `expr,;` to auto append, but the bare_statement rule leaves it indestinguishable from `expr`
			++j;
		}
		statement->size = 0;
		delete_ast(statement);
	}
	r->size = 0;
	delete_ast(r);
}

size_t fold_prec(ast *r){
	//expr_infix= expr_prefix (whitespace? op_infix whitespace? expr_prefix)*
	//op_infix= "->"|"$="|"*="|"/="|"%="|"<<="|">>="|"+="|"-="|"&="|"|="|"^="|"~&="|"~|="|"~^="|"&&="|"||="|"^^="|"!&&="|"!||="|"!^^="|"&&"|"||"|"^^"|"!&&"|"!||"|"!^^"|"<<"|">>"|"<=>"|">="|"<="|"=="|"!="|"<-"|">"|"<"|"="|"&"|"|"|"^"|"~&"|"~|"|"~^"|"+"|"-"|"*"|"/"|"%"|"$"|":"
	for(size_t i = 1; i < r->size; i += 2){
		operator op = str_infix_to_op(r->children[i]->text);
		r->children[i]->name = (char*)op;//overwrite the name of the parse node ("op_infix") with an enum.  sizeof(operator) <= sizeof(char*) so this is okay.
		r->children[i]->size = 2;
	}
	for(size_t i = 0; i < r->size; i += 2){
		r->children[i]->name = (char*)OP_ID;
	}
	ast **cur = r->children;
	return fold_prec_rec(&cur, r->size, -1);
}

/*
 * @param cur array of pointers to ast nodes
 * @param len the length of buf
 * @param prec the precedence of the preceding operator (-1 if no previous operator), used to find where to stop
 * @return the number of expr nodes needed for this ast node
 * this function is stupid levels of complicated, but its function is fairly monolithic
 */
size_t fold_prec_rec(ast ***cur, size_t len, int prec){
	ast *a = (*cur)[0];
	if(len == 1){
		return count_prefix(a);
	}
	ast *o = (*cur)[1];
	operator op = (operator)o->name;
	int prec_here = op_precedence[op];
	if(prec_here < prec || (prec_here == prec && op_associativity[prec] > 0)){
		return count_prefix(a);
	}
	o->children = *cur;
	*cur += 2;
	len -= 2;
	o->size = fold_prec_rec(cur, len, prec_here);
	return count_prefix(a) + 1 + fold_prec_rec(cur, len, prec);
}

size_t count_prefix(ast *r){
	//expr_prefix= (whitespace? op_prefix)* whitespace? expr_postfix
	//op_prefix= "++"|"--"|"+"|"-"|"!"|"~"|"*"|"&"
	if((operator)r->name != OP_ID){
		return 0;
	}else{
		return r->size - 1 + count_postfix(r->children[r->size - 1]);
	}
}

size_t count_postfix(ast *r){
	//expr_postfix= expr0 (whitespace? op_postfix)* whitespace?
	//op_postfix= "++"|"--"|".."|"?"|param_parens|list|access|declaration
	//expr0< declaration | atom
	//access= dot identifier
	//declaration= at atom
	return r->size + !strcmp("declaration", r->children[0]->name);
}

expression *transform_expr_node(expression *out, ast *o, expression *buf){
	//operator op;
	//size_t len;
	//char assign_undesignated;
	//atom_type type;
	//void *args[2];
	out->op = (operator)o->name;
	out->assign_undesignated = 0;
	out->type = ATOM_EXPR;
	if(out->op == OP_ID){
		return transform_prefix_node(out, o, buf);
	}else{
		out->len = 2;
		out->args[0] = buf;
		out->args[1] = buf = transform_expr_node(buf, o->children[0], buf + 1);
		return transform_expr_node(buf, o->children[1], buf + 1);
	}
}

expression *transform_prefix_node(expression *out, ast *o, expression *buf){
	for(size_t i = 0; i < o->size - 1; ++i){
		out->op = str_prefix_to_op(o->children[i]->text);
		out->len = 1;
		out->assign_undesignated = 0;
		out->type = ATOM_EXPR;
		out->args[0] = buf;
		out = buf++;
	}
	return transform_postfix_node(out, o->children[o->size - 1], buf);
}

expression *transform_postfix_node(expression *out, ast *o, expression *buf){
	//op_postfix= "++"|"--"|".."|"?"|param_parens|list|access|declaration
	//param_parens= lparen bare_statement whitespace? rparen
	//list= label_tag? lbrace bare_statement rbrace
	//access= dot identifier
	//declaration= at atom
	for(size_t i = o->size - 1; i; --i){
		out->assign_undesignated = 0;
		out->type = ATOM_EXPR;
		out->len = o->size + 1;
		if(o->size){
			if(!strcmp("param_parens", o->children[i]->name)){
				out->op = OP_APP;
				out->args[1] = um_transform_comp_statement(o->children[i]->children[0]);
			}else if(!strcmp("list", o->children[i]->name)){
				out->op = OP_IDX;
				out->args[1] = um_transform_comp_statement(o->children[i]->children[0]);
			}else if(!strcmp("access", o->children[i]->name)){
				out->op = OP_GET;
				out->args[1] = (char*)o->children[i]->children[0]->text;
				o->children[i]->children[0]->text = NULL;
			}else if(!strcmp("declaration", o->children[i]->name)){
				out->op = OP_NEWM;
				out->args[1] = malloc(1*sizeof(expression));
				um_transform_atom(out->args[1], o->children[i]->children[0]);
			}//otherwise we have a problem
		}
		out->args[0] = buf;
		out = buf++;
	}
	if(!strcmp("declaration", o->children[0]->name)){
		out->op = OP_NEWL;
		out->len = 1;
		out->assign_undesignated = 0;
		out->type = ATOM_EXPR;
		out->args[0] = buf;
		out = buf++;
		um_transform_atom(out, o->children[0]->children[0]);
	}else{
		um_transform_atom(out, o->children[0]);
	}
	return buf;
}

void delete_folded_expr_ast(ast *r){}//TODO: NYI NEEDS TO BE WRITTEN

void um_transform_expr(expression *out, ast *r){
	//expr= whitespace? expr_infix
	size_t expr_nodes_len = fold_prec(r) - 1;
	//fold_prec will rearrange the ast to account for operator precedence.
	//the end result of this is that r's children will be in postorder instead
	//of inorder, their names are changed from const *char's to string literals
	//to operator enums, and they are arranged into a tree with r->children[r->size - 1]
	//as the root.  The new nodes are really just the odd index nodes (zero indexed)
	//which represent the operators.  Their children arrays are taken as slices
	//of r->children and so cannot be freed.
	expression *expr_nodes = NULL;
	if(expr_nodes_len){
		expr_nodes = malloc(expr_nodes_len*sizeof(expression));
	}
	transform_expr_node(out, r->children[r->size - 1], expr_nodes);
	delete_folded_expr_ast(r);
}

void um_transform_atom(expression *out, ast *r){
	//atom= compound_statement | identifier | literal | parens | implicit__
	//literal= list | dict | block | int | float | complex | string | char
	
	//I've rewritten this file 3 times
	//and all of the naming conventions are inconsistent and I should refactor but until I finish
	//this I don't think the code base is even in a compileable state.  Then I have the fact that
	//right now I have to differentiate nodes in an expression tree and parenthetical subexpressions.
	//Currently I do that by having both be expression.type=ATOM_EXPR but nodes are .op=OP_* while
	//parentheticals are .op=OP_ID.  So I still have to deal with the other atom types.  Let's see...
	//compound_statement needs a new struct type in expression.h probably.  Identifier can use a C string.
	//literal can be a value (object.h), although I will have to extend it to allow container literals.
	//A container literal (list, dict, block) will initially be implemented as a block, where list and
	//dict have the assign_undesignated flag set.  I do not think I will enforce integral keys in lists
	//at this time.
	//parens is an expression
	//implicit__ needs no data, so having an atom type for it will be enough
	r = r->children[0];
	out->op = OP_ID;
	out->len = 1;
	out->assign_undesignated = 0;
	if(!strcmp("compound_statement", r->name)){
		out->type = ATOM_CSTMT;
		insert_cstmt((expression*)out->args, r);
	}else if(!strcmp("identifier", r->name)){
		out->type = ATOM_IDENT;
		out->args[0] = (char*)r->text;
		r->text = NULL;
	}else if(!strcmp("literal", r->name)){
		out->type = ATOM_VALUE;
		out->args[0] = malloc(1*sizeof(value));
		transform_literal(out->args[0], r);
	}else if(!strcmp("parens", r->name)){
		out->type = ATOM_EXPR;
		out->args[0] = malloc(1*sizeof(expression));
		um_transform_expr(out->args[0], r);
	}else{//implicit__
		out->type = ATOM_I_;
		out->len = 0;
	}
}


void insert_cstmt(expression *out, ast *r){
	//compound_statement= (whitespace? identifier | literal | parens whitespace? param_parens? whitespace? block)+
	//operator op;
	//size_t len;
	//char assign_undesignated;
	//atom_type type;
	//void *args[2];
	size_t cstmt_sections = r->size;
	out->args[0] = malloc(1*sizeof(block) +
	                      cstmt_sections*sizeof(expression[3]));
	block *repr = out->args[0];
	expression (*dblocks)[2] = out->args[0] + 1*sizeof(block);
	repr->len = cstmt_sections;
	for(size_t i; i < r->size; ++i){
		dblocks[i][0] = (expression){
			.op=OP_CSTMT,
			.len = i == r->size - 1 ? 1 : 2,
			.type=ATOM_EXPR,
			.args[0] = dblocks[i] + 1,
			.args[1] = dblocks[i] + 2,
		};
		um_transform_atom(dblocks[i] + 1, r->children[i]);//um_transform_atom takes r->children[0] automatically
		dblocks[i][2] = (expression){
			.op=OP_CSTMT_ARGS,
			.len = r->children[i]->size - 1,
			.type=ATOM_EXPR,
			.args[0] = um_transform_comp_statement(r->children[i]->children[1]),
			.args[1] = r->children[i]->size > 2 ? um_transform_comp_statement(r->children[i]->children[2]) : NULL,
		};
	}
}

expression *um_transform_comp_statement(ast *r){
	expression *ret = malloc(1*sizeof(expression));
	*ret = (expression){
		.op=OP_ID,
		.len=1,
		.type=ATOM_VALUE,
		.args[0] = malloc(1*sizeof(value)),
	};
	transform_value_comp_statement(ret->args[0], r);
	return ret;
}

void transform_value_comp_statement(value *out, ast *r){
	*out = (value){
		.type=VTYPE_BLOCK,
		.data = calloc(1, sizeof(block)),
	};
	transform_block_comp_statement(out->data, r);
}

void transform_block_comp_statement(block *out, ast *r){
	//bare_statement= (expr whitespace? comma)* expr?
	out->len = r->size;
	out->statements = malloc(out->len*sizeof(expression));
	for(size_t i = 0, j = 0; i < r->size; ++i){
		ast *expr = r->children[i];
		um_transform_expr(out->statements + j, expr);
		out->statements[j].assign_undesignated = 1;
		++j;
	}
}

void transform_literal(value *out, ast *r){
	//VTYPE_VOID, VTYPE_I, VTYPE_Z, VTYPE_Q, VTYPE_R, VTYPE_CZ, VTYPE_CQ, VTYPE_CR, VTYPE_STR, VTYPE_OBJ, VTYPE_BLOCK,
	//literal= list | dict | block | int | float | complex | string | char
	//list= label_tag? lbrace bare_statement rbrace
	//dict= label_tag? lbracket bare_statement rbracket
	//block= label_tag? whitespace? lbracket statement* whitespace? rbracket
	r = r->children[0];
	if(!strcmp("list", r->name)){
		transform_compound_literal(out, r);
	}else if(!strcmp("dict", r->name)){
		transform_compound_literal(out, r);
	}else if(!strcmp("block", r->name)){
		*out = (value){
			.type=VTYPE_BLOCK,
			.data = calloc(1, sizeof(block)),
		};
		um_transform_block(out->data, r);
	}else if(!strcmp("int", r->name)){
		transform_int_literal(out, r);
	}else if(!strcmp("float", r->name)){
		transform_float_literal(out, r);
	}else if(!strcmp("complex", r->name)){
		transform_complex_literal(out, r);
	}else if(!strcmp("string", r->name)){
		transform_string_literal(out, r);
	}else if(!strcmp("char", r->name)){
		transform_char_literal(out, r);
	}else{
		//TODO: handle error
	}
}

void transform_compound_literal(value *out, ast *r){
	*out = (value){
		.type=VTYPE_BLOCK,
		.data = calloc(1, sizeof(block)),
	};
	block *b = out->data;
	//list= label_tag? lbrace bare_statement rbrace
	//dict= label_tag? lbracket bare_statement rbracket
	*b = (block){0};
	ast *label = r->size ? r->children[0] : NULL;
	if(!strcmp("label_tag", label->name)){
		b->tag_len = label->length;
		b->tag = malloc(b->tag_len + 1);
		memcpy(b->tag, label->text, b->tag_len + 1);
		delete_ast(label);
	}else{
		label = NULL;
	}
	b->len = r->children[!!label]->size;
	b->statements = malloc(b->len*sizeof(expression));
	for(size_t i = !!label, j = 0; i < r->size; ++i){
		ast *expr = r->children[i];
		um_transform_expr(b->statements + j, expr);
		b->statements[j].assign_undesignated = 1;
		++j;
	}
}

intptr_t transform_digit_groups_base(ast *r, size_t base){
	const static int char_digit[] = {
	    ['0']=0, ['1']=1, ['2']=2, ['3']=3, ['4']=4, ['5']=5, ['6']=6, ['7']=7, ['8']=8, ['9']=9,
	    ['A']=10, ['B']=11, ['C']=12, ['D']=13, ['E']=14, ['F']=15,
	    ['a']=10, ['b']=11, ['c']=12, ['d']=13, ['e']=14, ['f']=15};
	intptr_t ret = 0;
	for(size_t i = 0; i < r->size; ++i){
		ast *c = r->children[i];
		for(size_t j = 0; j < c->length; ++j){//I'm literally never going to use C++
			if(c->text[j] == '\''){
				continue;
			}
			ret = ret*base + char_digit[(unsigned char)c->text[j]];
		}
	}
	return ret;
}

void transform_int_literal(value *out, ast *r){
	//int= int_b | int_o | int_h | int_d
	//int_b= b_pre [01]+ (squote [01]+)*
	//int_o= o_pre [0-7]+ (squote [0-7]+)*
	//int_h= h_pre [0-9a-fA-F]+ (squote [0-9a-fA-F]+)*
	//int_d= [0-9]+ (squote [0-9]+)*
	out->type = VTYPE_Z;
	ast *f = r->children[0];
	if(!strcmp("int_b", f->name)){
		out->data = (void*)transform_digit_groups_base(r, 2);
	}else if(!strcmp("int_o", f->name)){
		out->data = (void*)transform_digit_groups_base(r, 8);
	}else if(!strcmp("int_h", f->name)){
		out->data = (void*)transform_digit_groups_base(r, 16);
	}else if(!strcmp("int_d", f->name)){
		out->data = (void*)transform_digit_groups_base(r, 10);
	}
}

void transform_float_literal(value *out, ast *r){
	//float= scientific | subnormal | normal
	//scientific< subnormal | normal | [0-9]+ [Ee] [+\-]? [0-9]+
	//subnormal< "." [0-9]+
	//normal< [0-9]+ "." [0-9]*
	out->type = VTYPE_R;
	char buf[r->length + 1];
	memcpy(buf, r->text, r->length);
	buf[r->length] = '\0';
	*(double*)&out->data = strtod(buf, NULL);
}

void transform_complex_literal(value *out, ast *r){
	//complex= (float whitespace? I) | (float whitespace? [+\-] float whitespace? I)
	out->type = VTYPE_CR;
	out->data = malloc(sizeof(double complex));
	size_t buf_len = r->children[0]->length;
	if(r->size != 3 && r->children[r->size - 3]->length > buf_len){
		buf_len = r->children[r->size - 3]->length;
	}
	char buf[buf_len + 1];
	buf[buf_len] = '\0';
	memcpy(buf, r->children[0]->text, r->children[0]->length);
	double val_r, val_i;
	if(r->size == 3){//pure imaginary
		val_r = 0, val_i = strtod(buf, NULL);
	}else{//real and imaginary components
		val_r = strtod(buf, NULL);
		memcpy(buf, r->children[r->size - 3]->text, r->children[r->size - 3]->length);
		buf[r->children[r->size - 3]->length] = '\0';
		val_i = strtod(buf, NULL);
	}
	*(double complex*)out->data = CMPLX(val_r, val_i);
}

void transform_string_literal(value *out, ast *r){
	//string= dquote schar* dquote
	//schar< [^\\"\n] | esc_seq
	out->type = VTYPE_STR;
	out->data = malloc(sizeof(vstr) + r->size*sizeof(char));
	vstr *str = out->data;
	str->len = r->size;
	for(size_t i = 0; i < r->size; ++i){
		str->buf[i] = r->children[i]->text[0];
	}
}

void transform_char_literal(value *out, ast *r){
	//char= squote schar squote
	out->type = VTYPE_CH;
	*(char*)out->data = r->text[0];
}

