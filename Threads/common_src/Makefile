.PHONY: all build tests next-commit prev-commit first-commit last-commit

all: build

build:
	g++ -std=c++17 -ggdb -O0 -pedantic -Wall -D _POSIX_C_SOURCE=200809L liberror.cpp resolvererror.cpp resolver.cpp resolve_name.cpp -o resolve_name
	g++ -std=c++17 -ggdb -O0 -pedantic -Wall -D _POSIX_C_SOURCE=200809L liberror.cpp resolvererror.cpp resolver.cpp socket.cpp http_protocol.cpp client_http.cpp -o client_http
	g++ -std=c++17 -ggdb -O0 -pedantic -Wall -D _POSIX_C_SOURCE=200809L liberror.cpp resolvererror.cpp resolver.cpp socket.cpp echo_server.cpp -o echo_server

_tests:
	byexample --timeout 8 -l shell README.md

tests: build
	@make --no-print-directory _tests

next-commit:
	@git checkout `git rev-list --topo-order HEAD..main | tail -1`

prev-commit:
	@git checkout HEAD~1

first-commit:
	@git checkout `git rev-list --max-parents=0 main | tail -1`

last-commit:
	@git checkout main
