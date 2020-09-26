#!/bin/bash
assert () {
    expected="$1"
    input="$2"

    ./mcc.out "$input" > tmp.s
    gcc -o tmp.out tmp.s
    ./tmp.out
    actual="$?"

    if [ "$actual" = "$expected" ]; then
        echo "$input => $actual"
    else
        echo "$input => $expected expected, but got $actual"
        exit 1
    fi
}

assert 0 0
assert 42 42
assert 21 "5+20-4"
assert 13 "12 - 8  + 9" 
assert 41 " 12 + 34 - 5 "

echo OK