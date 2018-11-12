#!/usr/bin/env bash
bin/parser_runner parser interpret src/parsers/parser.pra src/parsers/umbrella.pra
bin/parser_runner parser stub src/parsers/parser.pra; true
bin/parser_runner stub stub src/parsers/parser.pra; true
bin/test/test_builtin_parsers
bin/test/test_builtin_transformers
bin/parser_runner umbrella print src/examples/finite_prime_heap.um
bin/test/test_umbrella_transform_scalar_literals
bin/test/test_umbrella_transform_compound_literals
bin/test/test_umbrella_transform_statements

