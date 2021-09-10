package main

import (
	"fmt"
	"strconv"
	"os"	
)

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)

func calc(operator int, values []int) int {
	x := values[0]
	fmt.Print(x)
	for i := 1; i < len(values); i++ {
		if operator == 1 {
			fmt.Print(" + ", values[i])
			x += values[i]
		} else if operator == 2 {
			fmt.Print(" - ", values[i])
			x -= values[i]
		} else {
			fmt.Print(" * ", values[i])
			x *= values[i]
		}
	}
	fmt.Print(" = ", x)
	fmt.Println("")
	return 0
}

func main() {
	if len(os.Args) > 3 {
		symbol := 0
		num := make([]int, 0, 100)
		if os.Args[1] == "add" {
			symbol = 1
		} else if os.Args[1] == "sub" {
			symbol = 2
		} else if os.Args[1] == "mult" {
			symbol = 3
		} else {
			fmt.Println("Symbol Error")
			return
		}
		for i := 2; i < len(os.Args); i++ {
			n, c := strconv.Atoi(os.Args[i])
			if c == nil {
				num = append(num, n)
			} else {
				fmt.Println("Symbol Error")
				return
			}
		}
		calc(symbol, num)
		return
	} else {
		fmt.Println("Symbol Error")
	}
}