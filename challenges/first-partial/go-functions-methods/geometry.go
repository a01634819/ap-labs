// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/
/* Alma Anguiano A01634819*/

// See page 156.

// Package geometry defines simple types for plane geometry.
//!+point
package main

import (
	"math"
	"time"
	"os"
	"fmt"	
	"math/rand"
	"strconv"	
)

type Point struct{ x, y float64 }

func (p Point) X() float64 {
	return p.x
}

func (p Point) Y() float64 {
	return p.y
}

// traditional function
func Distance(p, q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

// same thing, but as a method of the Point type
func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

//!-point

//!+path

// A Path is a journey connecting the points with straight lines.
type Path []Point

// Distance returns the distance traveled along the path.
func (path Path) Distance() float64 {
	sum := 0.0
	for i := range path {
		if i > 0 {
			x := path[i-1].Distance(path[i])
			sum += x
			fmt.Printf(" + %.2f",x)
		}else if i == 0 {
			x := path[i].Distance(path[len(path)-1])
			sum += x
			fmt.Printf("%.2f",x)
		}		
	}
	return sum
}

func main() {

	if len(os.Args) != 2 {
		fmt.Println("Error")
		return
	}

	edges, _ := strconv.Atoi(os.Args[1])

	if edges < 3 {
		fmt.Println("Error")
		return
	}

	x := Path{}
	for i := 0; i < edges; i++ {
		random := rand.NewSource(time.Now().UnixNano())
		random2 := rand.New(random)
		x = append(x, Point{random2.Float64()*100 - (-100) + (-100), random2.Float64()*100 - (-100) + (-100)})
		for x.intersec() {
			x[i] = Point{random2.Float64()*100 - (-100) + (-100), random2.Float64()*100 - (-100) + (-100)}
		}
	}

	fmt.Printf("- Generating a [%d] sides figure\n",edges)

	fmt.Printf("- Figure's vertices\n")

	for i := range x {
		fmt.Printf("   -( %.2f, %.2f)\n", x[i].X(), x[i].Y())
	}

	fmt.Println("- Figure's Perimeter")
	fmt.Printf("  - ")
	Per := x.Distance()
	fmt.Printf(" = %.2f", Per)
}

func doIntersect(p1, q1, p2, q2 Point) bool{
    o1 := orientation(p1, q1, p2);
    o2 := orientation(p1, q1, q2);
    o3 := orientation(p2, q2, p1);
    o4 := orientation(p2, q2, q1);
  
    if (o1 != o2 && o3 != o4){
        return true;
	}
    if (o1 == 0 && onSegment(p1, p2, q1)) {
		return true;
	}
    if (o2 == 0 && onSegment(p1, q2, q1)) {
		return true;
	}
    if (o3 == 0 && onSegment(p2, p1, q2)) {
		 return true;
	}
    if (o4 == 0 && onSegment(p2, q1, q2)) {
		 return true;
	}
    return false; 
}

func orientation(p, q , r Point) float64 {
    val := (q.Y() - p.Y()) * (r.X() - q.X()) - (q.X() - p.X()) * (r.Y() - q.Y());
    if (val == 0){
		return 0;
	} 
	if (val > 0){
		return 1;
	}
	return 2;
}

func onSegment(p Point, q Point, r Point) bool{
    if (q.X() <= math.Max(p.X(), r.X()) && (q.X() >= math.Min(p.X(), r.X()) && (q.Y() <= math.Max(p.Y(), r.Y()) && (q.Y() >= math.Min(p.Y(), r.Y()))))) {
		return true	
	}
	return false
}

func (n Path) intersec() bool {
	var x bool
	for i := 0; i < len(n)-3 && !x; i++ {
		x = doIntersect(n[i], n[i+1], n[i+2], n[i+3])
	}
	return x
}

//!-path
