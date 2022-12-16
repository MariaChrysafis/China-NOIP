#![allow(warnings)]

use std::io::{BufWriter, stdin, stdout, Write};
use std::vec;
use std::cmp::max;
use std::cmp::min;
use std::collections::{BTreeSet, HashMap, HashSet};
use std::collections::vec_deque::VecDeque;
use std::hash::Hash;
use std::io::{self, BufRead};
use std::mem;
//use multiset::HashMultiSet;


#[derive(Default)]
struct Scanner {
    buffer: Vec<String>,
}

impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Faild read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

fn main() {
    let mut scan = Scanner::default();
    let out = &mut BufWriter::new(stdout());
    let n: usize = scan.next::<usize>();
    let mut arr: Vec<i32> = vec![0; n];
    for i in 0..n {
        arr[i] = scan.next::<i32>();
    }
    let average: i32 = arr.iter().sum::<i32>()/(n as i32);
    let mut ans: i32 = 0;
    for i in 0..(n - 1) {
        if arr[i] != average {
            arr[i + 1] -= average - arr[i];
            arr[i] += average - arr[i];
            ans += 1;
        }
    }
    println!("{}", ans);
}
