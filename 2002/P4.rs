#![allow(warnings)]

use std::io::{BufWriter, stdin, stdout, Write};
use std::vec;
use std::cmp::max;
use std::cmp::min;
use std::collections::{BTreeSet, HashMap, HashSet};
use std::collections::vec_deque::VecDeque;
use std::fs::soft_link;
use std::hash::Hash;
use std::io::{self, BufRead};
use std::mem;
use std::process::exit;
use std::ptr::hash;

fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

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

fn split_x(vec: Vec<(i32, i32)>, x: i32) -> (Vec<(i32, i32)>, Vec<(i32, i32)>){
    let mut vec1: Vec<(i32, i32)> = Vec::new();
    let mut vec2: Vec<(i32, i32)> = Vec::new();
    for i in 0..vec.len() {
        if vec[i].0 <= x {
            vec1.push(vec[i]);
        } else {
            vec2.push(vec[i]);
        }
    }
    return (vec1, vec2);
}

fn split_y(vec: Vec<(i32, i32)>, x: i32) -> (Vec<(i32, i32)>, Vec<(i32, i32)>){
    let mut vec1: Vec<(i32, i32)> = Vec::new();
    let mut vec2: Vec<(i32, i32)> = Vec::new();
    for i in 0..vec.len() {
        if vec[i].1 <= x {
            vec1.push(vec[i]);
        } else {
            vec2.push(vec[i]);
        }
    }
    return (vec1, vec2);
}

fn solve (vec: Vec<(i32, i32)>, k: usize) -> i32 {
    if vec.is_empty() {
        return 0;
    }
    if k == 1 {
        let mut max_x = vec.iter().map(|&x| x.0).max().unwrap();
        let mut max_y = vec.iter().map(|&x| x.1).max().unwrap();
        let mut min_x = vec.iter().map(|&x| x.0).min().unwrap();
        let mut min_y = vec.iter().map(|&x| x.1).min().unwrap();
        return (max_x - min_x) * (max_y - min_y);
    }
    let mut ok: Vec<i32> = vec![-1, 0, 500, 501];
    for i in 0..vec.len() {
        ok.push(vec[i].0);
        ok.push(vec[i].1);
    }
    let mut pos: Vec<i32> = Vec::new();
    for x in ok.iter() {
        let splitx = split_x(vec.clone(), *x);
        let splity = split_y(vec.clone(), *x);
        pos.push(solve(splitx.0.clone(), k - 1) + solve(splitx.1.clone(), 1));
        pos.push(solve(splity.0.clone(), k - 1) + solve(splity.1.clone(), 1));
    }
    return *(pos.iter().min().unwrap());

}

fn main() {
    let mut scan = Scanner::default();
    let n = scan.next::<usize>();
    let k = scan.next::<usize>();
    let mut vec: Vec<(i32, i32)> = Vec::new();
    for _ in 0..n {
        vec.push((scan.next::<i32>(), scan.next::<i32>()));
    }
    println!("{}", solve(vec.clone(), k));

}
