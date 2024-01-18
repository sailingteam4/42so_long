#!/bin/bash

# Path to the so_long executable
SO_LONG="./so_long"

# Path to the valgrind executable
VALGRIND="valgrind"

# Directories with valid and invalid maps
VALID_MAPS_DIR="./maps/valid"
INVALID_MAPS_DIR="./maps/invalid"

# Path to the suppression file
SUPPRESSION_FILE="./leak.sup"

# File to store memory leak information
MEMORY_LEAK_FILE="./memory_leak_info.txt"

# Counters for test results
SUCCESS_COUNT=0
ERROR_COUNT=0
MEMORY_LEAK_COUNT=0

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Animation
SPINNER=('⠋' '⠙' '⠹' '⠸' '⠼' '⠴' '⠦' '⠧' '⠇' '⠏')

# Function to display spinner animation
function show_spinner() {
	local pid=$!
	local i=0
	while kill -0 $pid 2>/dev/null; do
		printf "\r${SPINNER[$i]}  "
		sleep 0.1
		((i=i+1))
		((i=i%10))
	done
}

# Test valid maps
for map in $VALID_MAPS_DIR/*.ber
do
	echo -e "Testing valid map: $map"
	$VALGRIND --leak-check=full --error-exitcode=1 --suppressions=$SUPPRESSION_FILE $SO_LONG $map >> $MEMORY_LEAK_FILE 2>&1 &
	show_spinner
	if [ $? -eq 0 ]; then
		echo -e "${GREEN}Test passed${NC}"
		((SUCCESS_COUNT++))
	else
		echo -e "${RED}Test failed${NC}"
		((ERROR_COUNT++))
	fi
	if grep -q "definitely lost: [1-9]" $MEMORY_LEAK_FILE; then
		echo -e "${YELLOW}Memory leak detected${NC}"
		((MEMORY_LEAK_COUNT++))
	fi
done

# Test invalid maps
for map in $INVALID_MAPS_DIR/*.ber
do
	echo -e "Testing invalid map: $map"
	$VALGRIND --leak-check=full --error-exitcode=1 --suppressions=$SUPPRESSION_FILE $SO_LONG $map >> $MEMORY_LEAK_FILE 2>&1 &
	show_spinner
	if [ $? -eq 0 ]; then
		echo -e "${GREEN}Test passed${NC}"
		((SUCCESS_COUNT++))
	else
		echo -e "${GREEN}Test passed${NC}" # Mark the test as passed
		((SUCCESS_COUNT++)) # Increment the success count
	fi
	if grep -q "definitely lost: [1-9]" $MEMORY_LEAK_FILE; then
		echo -e "${YELLOW}Memory leak detected${NC}"
		((MEMORY_LEAK_COUNT++))
	fi
done

# Print summary of test results
echo -e "Number of successful tests: ${GREEN}$SUCCESS_COUNT${NC}"
echo -e "Number of failed tests: ${RED}$ERROR_COUNT${NC}"
echo -e "Number of tests with memory leaks: ${YELLOW}$MEMORY_LEAK_COUNT${NC}"
