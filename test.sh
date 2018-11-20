#!/usr/bin/env bash
bin/parser_runner parser interpret src/parsers/parser.pra src/parsers/umbrella.pra
bin/test/test_builtin_parsers
bin/test/test_builtin_transformers

