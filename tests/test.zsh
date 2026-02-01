#!/bin/zsh

PROGRAM="./so_long"

BLUE='\033[0;34m'
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
GRAY='\033[0;90m'
NC='\033[0m'
GREY='\033[0;90m'

COL1_WIDTH=40

VALID_MAPS_DIR="tests/maps/valid"
INVALID_MAPS_DIR="tests/maps/invalid"
INVALID_MAPS=("")
VALID_MAPS=()

STDOUT_FILE="/tmp/so_long_stdout"
STDERR_FILE="/tmp/so_long_stderr"

main()
{
	populate_maps
	test_invalid_maps
	test_valid_maps
}

populate_maps()
{
	local file

	for file in "$INVALID_MAPS_DIR"/*; do
		[[ -f "$file" ]] && INVALID_MAPS+=("${file:t}")
	done

	for file in "$VALID_MAPS_DIR"/*; do
		[[ -f "$file" ]] && VALID_MAPS+=("${file:t}")
	done
}

test_invalid_maps()
{
	local map ret_code full_path stdout_got stderr_got

	for map in "${INVALID_MAPS[@]}"; do
		printf "${GREY}⇢${BLUE} %-${COL1_WIDTH}s${GREY} ⇢ should print nothing to stdout, at least 'Error\\\n' to stderr and return > 0" "$PROGRAM $map"
		[[ -n "$map" ]] && full_path="${INVALID_MAPS_DIR}/${map}" || full_path="$map"
		"$PROGRAM" "$full_path" > "$STDOUT_FILE" 2> "$STDERR_FILE"
		ret_code=$?
		
		stdout_got=$(cat -e "$STDOUT_FILE")
		stderr_got=$(cat -e "$STDERR_FILE")
		
		if [[ -z "$stdout_got" ]] && [[ "$stderr_got" == Error\$* ]] && [[ $ret_code -gt 0 ]]; then
			echo " ${GREEN}✔${NC}"
		else
			echo " ${RED}✖${NC}"
		fi
	done
}

test_valid_maps()
{
	local map ret_code full_path stderr_got

	for map in "${VALID_MAPS[@]}"; do
		printf "${GREY}⇢${BLUE} %-${COL1_WIDTH}s${GREY} ⇢ should print nothing to stderr and return 0" "$PROGRAM $map"
		[[ -n "$map" ]] && full_path="${VALID_MAPS_DIR}/${map}" || full_path="$map"
		"$PROGRAM" "$full_path" > /dev/null 2> "$STDERR_FILE"
		ret_code=$?
		
		stderr_got=$(cat -e "$STDERR_FILE")
		
		if [[ -z "$stderr_got" ]] && [[ $ret_code -eq 0 ]]; then
			echo " ${GREEN}✔${NC}"
		else
			echo " ${RED}✖${NC}"
		fi
	done
}

main
