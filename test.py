import betest as B
import ctypes

class PraserPosition(ctypes.Structure):
	_fields_ = [
		("start", ctypes.c_char_p),
		("end", ctypes.c_char_p),
		("curr", ctypes.c_char_p)
	]
	
	@staticmethod
	def make(s):
		start = ctypes.c_char_p(s.encode())
		return PraserPosition(start, ctypes.c_char_p(ctypes.addressof(start) + len(s)), start)

clibs = B.bind_libraries("betest_imports.json")

@B.unit()
def parse_hex2():
	print("Allocating ast")
	clibs["alloc_ast"].restype = ctypes.c_void_p
	ast = clibs["alloc_ast"]()
	print("initializing parser position")
	pos = PraserPosition.make("x41")
	print("parsing 2 digit hex string")
	if clibs["parse_hex2"](ast, ctypes.byref(pos)) == 0:
		raise AssertionError("parse_hex2 failed to parse \"x41\"")
	print("printing ast")
	clibs["print_ast"](ast)
	print("deleting ast")
	clibs["delete_ast"](ast)
	return True

B.run_all()

