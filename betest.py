import json
import ctypes
import random
import os
import atexit
import subprocess

wrapped_libs = []
def remove_wrapped_libs():
	for lib in wrapped_libs:
		os.remove(lib)

#atexit.register(remove_wrapped_libs)

def open_obj_f(obj_f_name):
	if obj_f_name.endswith(".a"):
		wrapped_name = obj_f_name[:-1] + "so"
		print("Wrapping static library")
		if 0 == subprocess.call(["gcc", "--coverage", "-shared", "-o", wrapped_name, "-Wl,--whole-archive", obj_f_name, "-Wl,--no-whole-archive"]):
			wrapped_libs.append(wrapped_name)
			return ctypes.CDLL(wrapped_name)
		raise ValueError("Couldn't make static library shared")
	return ctypes.CDLL(obj_f_name)

FUNCTION_PTR = ctypes.POINTER(ctypes.CFUNCTYPE(ctypes.c_int))

def bind_libraries(in_f_path):
	with open(in_f_path, "r") as in_f:
		imports = json.load(in_f)
	
	obj_fs = dict()
	for obj_f_name in imports:
		try:
			obj_f = open_obj_f(os.path.abspath(obj_f_name))
		except Exception as e:
			print("Could not open \"{}\"".format(obj_f_name))
			print(e)
			continue
		obj_fs[obj_f_name] = obj_f

	bindings = dict()
	for obj_f_name, these_bindings in imports.items():
		obj_f = obj_fs[obj_f_name]
		for func_name, bound_name in these_bindings.items():
			try:
				if func_name.startswith("*"):
					func = FUNCTION_PTR(obj_f[func_name[1:]]).contents
				else:
					func = obj_f[func_name]
			except Exception as e:
				print("Could not find function \"{}\" in \"{}\"".format(func_name, obj_f_name))
				print(e)
				continue
			bindings[bound_name] = func
	
	return bindings

class Suite:
	def __init__(self, rng=None):
		if rng is None:
			rng = random
		self.tests = []
		self.rng = rng
	
	def append(self, test):
		self.tests.append(test)
	
	def __iter__(self):
		return iter(self.tests)
	
	def __len__(self):
		return len(self.tests)

default_suite = Suite()
suites = [default_suite]

def get_default_suite():
	return default_suite

def get_suite():
	suites.append([])
	return suites[-1]

def unit(suite=None, result=None):
	if suite is None:
		suite = default_suite
	if result is None:
		result = True, None
	def unit_inner(func):
		def closure(*args, **kwargs):
			try:
				res = func(*args, **kwargs)
			except Exception as e:
				if result[1] is not None and isinstance(e, result[1]):
					return True
				print("Test threw a(n) {}: \"{}\"".format(type(e), e))
				return False
			return result[1] is None and res == result[0]
		closure.__annotations__ = func.__annotations__
		closure.__doc__ = func.__doc__
		closure.__name__ = func.__name__
		closure.__qualname__ = func.__qualname__
		closure.__dict__["test_type"] = "unit"
		suite.append(closure)
		return func
	return unit_inner

def property(gen, runs, suite=None):
	if suite is None:
		suite = default_suite
	def property_inner(func):
		def closure(*args, **kwargs):
			arg_gen = gen.get_generator(suite.rng)
			for i in range(1, runs + 1):
				arg = next(arg_gen)
				if not func(arg, *args, **kwargs):
					print("Property {} failed on input {}.  Trying to reduce input...".format(func.__name__, arg))
					print("Input reduction not yet implemented")
					return False, arg
			return True, None
		closure.__annotations__ = func.__annotations__
		closure.__doc__ = func.__doc__
		closure.__name__ = func.__name__
		closure.__qualname__ = func.__qualname__
		closure.__dict__["test_type"] = "property"
		suite.append(closure)
		return func
	return property_inner

def call_with(func, *args, **kwargs):
	def closure():
		return func(*args, **kwargs)
	closure.__annotations__ = {'return':func.__annotations__['return']}
	closure.__doc__ = "Calls the wrapped function with memoized arguments.  Wrapped doc:\n" + func.__doc__
	closure.__name__ = func.__name__
	closure.__qualname__ = func.__qualname__
	return closure

def run_all():
	test_count = sum(len(suite) for suite in suites)
	tests_passed = 0
	print("\x1b[1;34mRunning {} tests:\x1b[0m".format(test_count))
	for i, suite in enumerate(suites, 1):
		suite_test_count = len(suite)
		suite_tests_passed = 0
		print("\x1b[1;34mRunning suite {} with {} test(s):\x1b[0m".format(i, suite_test_count))
		for j, test in enumerate(suite, 1):
			passed = False
			if test.test_type == "unit":
				if test():
					passed = True
			elif test.test_type == "property":
				res, err = test()
				if res:
					passed = True
			else:
				print("\x1b[1;31mError: invalid type of test registered ({})\x1b[0m".format(test.test_type))
			if passed:
				print("\x1b[1;32mTest {}.{} \"{}\" passed\x1b[0m".format(i, j, test.__name__))
				suite_tests_passed += 1
			else:
				print("\x1b[1;31mTest {}.{} \"{}\" failed\x1b[0m".format(i, j, test.__name__))
		tests_passed += suite_tests_passed
		print("\x1b[1;34mFinished suite {}. {}/{} ({}%) tests passed\x1b[0m".format(i, suite_tests_passed, suite_test_count, "N/A" if suite_test_count == 0 else 100*suite_tests_passed/suite_test_count))
	print("\x1b[1;34mFinished all tests. {}/{} ({}%) passed\x1b[0m".format(tests_passed, test_count, "N/A" if test_count == 0 else 100*tests_passed/test_count))

class ArgumentGenerator:
	def get_generator(self, rng):
		pass
	
	def get_reducer(self, arg):
		pass

class UniformIntGenerator(ArgumentGenerator):
	def __init__(self, a, b):
		self.a = a
		self.b = b
	
	def get_generator(self, rng):
		def generator():
			while True:
				yield rng.randrange(self.a, self.b)
		return generator()
	
	def get_reducer(self, arg):
		pass

class UniformDoubleGenerator(ArgumentGenerator):
	def __init__(self, a, b):
		self.a = a
		self.b = b
	
	def get_generator(self, rng):
		def generator():
			while True:
				yield rng.uniform(self.a, self.b)
		return generator()
	
	def get_reducer(self, arg):
		pass

