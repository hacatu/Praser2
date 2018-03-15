import betest as B
import ctypes

class PraserPosition(ctypes.Structure):
	_fields_ = [
		("start", ctypes.c_char_p),
		("end", ctypes.c_char_p),
		("curr", ctypes.c_char_p)
	]
	
	def __init__(self, s):
		self.start = ctypes.c_char_p(s)
		self.end = self.start + len(s)
		self.pos = self.start

clibs = B.bind_libraries("betest_imports.json")

@B.unit()
def parse_hex2():
	print("Allocating ast")
	ast = clibs["alloc_ast"]()
	pos = PraserPosition("x41")
	print("parsing 2 digit hex string")
	if clibs["parse_hex2"](ast, ctypes.byref(pos)) == 0:
		raise AssertionError("parse_hex2 failed to parse \"x41\"")
	print("printing ast")
	clibs["print_ast"](ast)
	print("deleting ast")
	clibs["delete_ast"](ast)
	return True

B.run_all()

