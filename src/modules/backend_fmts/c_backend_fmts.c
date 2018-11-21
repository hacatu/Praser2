/*
pattern = group+
group = option+
option = atom quantifier?
atom = state | string | charset | invset

======pattern======
const char *parse_<rule_name>(ast *t, position *p){
	[if not a generated rule] set_tag(t, <rule_name>_tag);
	[group]...
	return NULL;
}

======group[>1]======
do{
	const char *err = NULL, *terr = NULL;
	position s = *p, e = s;
	[option (err=terr)]...
	if(e.curr > s.curr){
		*p = e;
		return err;
	}
	return "[options_spec]";
}while(0);

======group[1]======
{
	const char *err;
	position s = *p;
	[atom_quantified (err=err)]
	if(err){
		return err;
	}
}

======option======
[atom_quantified]
if(!terr){
	break;
}
if(p->curr > s.curr){
	err = terr;
	e = *p;
	*p = s;
}

======atom_quantified======
[if not quantified: atom_once]
[if quantifier is "?": atom_optional]
[if quantifier is "*": atom_multiple]
[if quantifier is "+": atom_repeated]

======atom_once======
[atom (t=t)]

======atom_optional======
{
	position l = *p;
	[atom (t=t)]
	if(<err>){
		*p = l;
		<err> = NULL;
	}
}

======atom_multiple======
{
	position l;
	ast *c;
	while(1){
		l = *p;
		c = alloc_ast();
		[atom (t=c)]
		if(<err>)break;
		merge_ast(t, c);
	}
	delete_ast(c);
	*p = l;
	<err> = NULL;
}

======atom_repeated======
{
	position l;
	ast *c;
	char matched = 0;
	while(1){
		l = *p;
		c = alloc_ast();
		[atom (t=c)]
		if(<err>)break;
		matched = 1;
		merge_ast(t, c);
	}
	delete_ast(c);
	*p = l;
	if(matched){
		<err> = NULL;
	}
}

======atom======
[if state: atom_state]
[if string: atom_string]
[if charset: atom_charset]
[if invset: atom_invset]

======atom_string======
<err> = read_string(<atom->text>, <t>, p) ? NULL : "<atom->text>";

======atom_charset======
<err> = read_charset([charset_spec], <t>, p) ? NULL : "[[charset_spec]]";

======atom_invset======
<err> = read_invset([invset_spec], <t>, p) ? NULL : "[[invset_spec]]";

======atom_state======
[if assigner is "=": atom_append]
[if assigner is "<": atom_merge]
[if assigner is ":": atom_skip]

======atom_append======
ast *r = alloc_ast();
<err> = [name](s, r, p);
if(<err>){
	delete_ast(r);
}else{
	append_ast(<t>, r);
}

======atom_merge======
<err> = [name](s, <t>, p);

======atom_skip======
ast *r = &(ast){0};
<err> = [name](s, r, p);
clear_ast(r);
*/

#include <inttypes.h>

const char
src_pre_fmt[] =
"#include <stdio.h>\n"
"#include <stdlib.h>\n"
"#include <string.h>\n"
"#include \"parser.h\"\n"
"\n"
"#pragma GCC diagnostic ignored \"-Wunused-const-variable\"\n"
"\n",
src_mid_fmt[] =
"\n",
pattern_decl_fmt[] =//1$<rule_name>
"const char *%1$s_parser(ast*, position*);\n"
"static const char %1$s_tag[] = \"%1$s\";\n",
pattern_pre_merge_fmt[] =//1$<rule_name>
"const char *%1$s_parser(ast *t, position *p){\n",
pattern_pre_fmt[] =//1$<rule_name>
"const char *%1$s_parser(ast *t, position *p){\n"
	"\tset_tag(t, %1$s_tag);\n",
	//[group]...
pattern_post_fmt[] =
	"\treturn NULL;\n"
"}\n\n",
group_pre_fmt[] =
	"\tdo{\n"
		"\t\tconst char *err = NULL, *terr = NULL;\n"
		"\t\tposition s = *p, e = s;\n"
		"\t\tsize_t length_a = t->length, size_a = t->size;\n",
		//[option]...
group_post1_fmt[] =
		"\t\tif(e.curr > s.curr){\n"
			"\t\t\t*p = e;\n"
			"\t\t\treturn err;\n"
		"\t\t}\n"
		"\t\treturn ",//[option_spec]
group_post2_fmt[] =
";\n"
	"\t}while(0);\n",
group_singular_pre_fmt[] =
	"\t{\n"
		"\t\tconst char *err = NULL;\n",
		//[atom_quantified (err=err)]
group_singular_post_fmt[] =
		"\t\tif(err){\n"
			"\t\t\treturn err;\n"
		"\t\t}\n"
	"\t}\n",
option_fmt[] =
		//[atom_quantified (err=terr)]
		"\t\tif(!terr){break;}\n"
		"\t\tif(p->curr > s.curr){\n"
			"\t\t\tt->length = length_a, t->size = size_a;\n"
			"\t\t\terr = terr;\n"
			"\t\t\te = *p;\n"
			"\t\t\t*p = s;\n"
		"\t\t}\n",
atom_once_pre_fmt[] =
		"\t\t{\n",
			//[atom (t=t)]
atom_once_post_fmt[] =
		"\t\t}\n",
atom_optional_pre_fmt[] =
		"\t\t{\n"
			"\t\t\tposition l = *p;\n",
			//[atom (t=t)]
atom_optional_post_fmt[] =//1$<err>
			"\t\t\tif(%1$s){\n"
				"\t\t\t\t*p = l;\n"
				"\t\t\t\t%1$s = NULL;\n"
			"\t\t\t}\n"
		"\t\t}\n",
atom_multiple_pre_fmt[] =
		"\t\t{\n"
			"\t\t\tposition l;\n"
			"\t\t\tast *c;\n"
			"\t\t\twhile(1){\n"
				"\t\t\t\tl = *p;\n"
				"\t\t\t\tc = alloc_ast();\n",
				//[atom (t=c)]
atom_multiple_post_fmt[] =//1$<err>
				"\t\t\t\tif(%1$s)break;\n"
				"\t\t\t\tmerge_ast(t, c);\n"
			"\t\t\t}\n"
			"\t\t\tdelete_ast(c);\n"
			"\t\t\t*p = l;\n"
			"\t\t\t%1$s = NULL;\n"
		"\t\t}\n",
atom_repeated_pre_fmt[] =
		"\t\t{\n"
			"\t\t\tposition l;\n"
			"\t\t\tast *c;\n"
			"\t\t\tchar matched = 0;\n"
			"\t\t\twhile(1){\n"
				"\t\t\t\tl = *p;\n"
				"\t\t\t\tc = alloc_ast();\n",
				//[atom (t=c)]
atom_repeated_post_fmt[] =//1$<err>
				"\t\t\t\tif(%1$s)break;\n"
				"\t\t\t\tmatched = 1;\n"
				"\t\t\t\tmerge_ast(t, c);\n"
			"\t\t\t}\n"
			"\t\t\tdelete_ast(c);\n"
			"\t\t\t*p = l;\n"
			"\t\t\tif(matched){\n"
				"\t\t\t\t%1$s = NULL;\n"
			"\t\t\t}\n"
		"\t\t}\n",
atom_string_fmt[] =//1$<err>, 2$<t>, 3$<atom->text>
				"\t\t\t\t%1$s = read_string(\"%3$s\", %2$s, p) ? NULL : \"%3$s\";\n",
atom_charset_fmt[] =//1$<err>, 2$<t>, 3$[charset_spec]
				"\t\t\t\t%1$s = read_charset_prefix(\"%3$s\", %2$s, p) ? NULL : \"%3$s\";\n",
atom_append_fmt[] =//1$<err>, 2$<t>, 3$[name]
				"\t\t\t\tast *r = alloc_ast();\n"
				"\t\t\t\t%1$s = %3$s_parser(r, p);\n"
				"\t\t\t\tif(%1$s){\n"
					"\t\t\t\t\tdelete_ast(r);\n"
				"\t\t\t\t}else{\n"
					"\t\t\t\t\tappend_ast(%2$s, r);\n"
				"\t\t\t\t}\n",
atom_merge_fmt[] =//1$<err>, 2$<t>, 3$[name]
				"\t\t\t\t%1$s = %3$s_parser(%2$s, p);\n",
atom_skip_fmt[] =//1$<err>, 2$[name]
				"\t\t\t\tast *r = &(ast){0};\n"
				"\t\t\t\t%1$s = %2$s_parser(r, p);\n"
				"\t\t\t\tclear_ast(r);\n",
state_name_fmt[] =//1$[name]
"%1$s",
state_name_fmt_trunc[] =//1$[name], 2$[len]
"%1$.*2$s",
state_name_generated_fmt[] =//1$[offset]
"gen%1$#"PRIXPTR;

