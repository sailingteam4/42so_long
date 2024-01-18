#!/bin/sh

# Define colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Compile the project
echo "==================== Compiling the project ===================="
make
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed. Exiting...${NC}"
    exit 1
fi
echo -e "${GREEN}Compilation successful.${NC}"

# Counters
success_count=0
error_count=0
leak_count=0

# Get all valid test maps
valid_maps=$(find maps/valid -type f)

for map in $valid_maps
do
    echo "==================== Running the program with valid map ${map} ===================="
    ./so_long ${map}
    if [ $? -ne 0 ]; then
        echo -e "${RED}Program exited with an error. Continuing with the next map...${NC}"
        error_count=$((error_count+1))
        continue
    fi

    # Check for memory leaks
    echo "==================== Checking for memory leaks ===================="
    valgrind --leak-check=full --suppressions=leak.sup --show-leak-kinds=all --error-exitcode=1 --errors-for-leak-kinds=all ./so_long ${map} > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${RED}Memory leaks detected. Continuing with the next map...${NC}"
        leak_count=$((leak_count+1))
        continue
    fi
    echo -e "${GREEN}No memory leaks detected.${NC}"
    success_count=$((success_count+1))
done

# Get all invalid test maps
invalid_maps=$(find maps/invalid -type f)

for map in $invalid_maps
do
    echo "==================== Running the program with invalid map ${map} ===================="
    ./so_long ${map}
    if [ $? -eq 0 ]; then
        echo -e "${RED}Program did not exit with an error for invalid map. Continuing with the next map...${NC}"
        error_count=$((error_count+1))
        continue
    fi
    echo -e "${GREEN}Program correctly exited with an error for invalid map.${NC}"
    success_count=$((success_count+1))
done

echo "==================== Testing completed ===================="
echo "Summary:"
echo -e "${GREEN}Successful tests: ${success_count}${NC}"
echo -e "${RED}Failed tests: ${error_count}${NC}"
echo -e "${RED}Tests with memory leaks: ${leak_count}${NC}"