#!/usr/bin/env bash
bin/parser_runner generated interpret src/parser.pra src/umbrella.pra
bin/parser_runner generated stub src/parser.pra; true
bin/parser_runner stub stub src/parser.pra; true
bin/test/test_builtin_parsers
bin/test/test_builtin_transformers
bin/parser_runner umbrella print src/examples/finite_prime_heap.um

