#!/bin/bash
echo "Case 1"
java -Xss10M Assig4 320000 10 false > A4-32-Random.txt

echo "Case 2"
java -Xss10M Assig4 640000 10 false > A4-64-Random.txt

echo "Case 3"
java -Xss10M Assig4 10000 10 true > A4-1-Sorted.txt

echo "Case 4"
java -Xss10M Assig4 20000 10 true > A4-2-Sorted.txt

echo "Case 5"
java -Xss10M Assig4 1280000 10 false > A4-128-Random.txt

echo "Case 6"
java -Xss10M Assig4 2560000 10 false > A4-256-Random.txt

echo "Case 7"
java -Xss10M Assig4 5120000 10 false > A4-512-Random.txt

echo "Case 8"
java -Xss10M Assig4 40000 10 true > A4-4-Sorted.txt

echo "Case 9"
java -Xss10M Assig4 80000 10 true > A4-8-Sorted.txt