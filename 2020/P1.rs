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

use std::{cmp, fmt};
use std::ops::{Add, Sub, Mul, Div};

#[derive(Debug)]
#[derive(Clone)]
pub struct Fraction {
    numerator: i128,
    denominator: i128,
}

impl Fraction {
    /// Creates a new fraction with the given numerator and denominator
    /// Panics if given a denominator of 0
    pub fn new(numerator: i128, denominator: i128) -> Self {
        if denominator == 0 { panic!("Tried to create a fraction with a denominator of 0!") }
        if denominator < 0 {
            Self { numerator: -numerator, denominator: -denominator }
        } else {
            Self { numerator, denominator }
        }
    }

    /// Returns a new Fraction that is equal to this one, but simplified
    pub fn reduce(&self) -> Self {
        // Use absolute value because negatives
        let gcd = gcd(self.numerator.abs(), self.denominator.abs());
        Self {
            numerator: (self.numerator / gcd),
            denominator: (self.denominator / gcd),
        }
    }

    /// Returns a decimal equivalent to this Fraction
    pub fn to_decimal(&self) -> f64 {
        self.numerator as f64/ self.denominator as f64
    }
}

impl fmt::Display for Fraction {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let temp = self.reduce();
        if temp.denominator == 1 {
            write!(f, "{}", temp.numerator)
        } else {
            write!(f, "{}/{}", temp.numerator, temp.denominator)
        }
    }
}

impl cmp::PartialEq for Fraction {
    fn eq(&self, other: &Fraction) -> bool {
        let simp_self = self.reduce();
        let simp_other = other.reduce();
        simp_self.numerator == simp_other.numerator &&
            simp_self.denominator == simp_other.denominator
    }
}

impl cmp::Eq for Fraction {}

impl cmp::PartialOrd for Fraction {
    fn partial_cmp(&self, other: &Fraction) -> Option<cmp::Ordering> {
        self.to_decimal().partial_cmp(&other.to_decimal())
    }
}

impl<'a> Add for &'a Fraction {
    type Output = Fraction;

    fn add(self, other: Self) -> Fraction {
        Fraction {
            numerator: (self.numerator * other.denominator + other.numerator * self.denominator),
            denominator: (self.denominator * other.denominator),
        }
    }
}

impl<'a> Sub for &'a Fraction {
    type Output = Fraction;

    fn sub(self, other: Self) -> Fraction {
        Fraction {
            numerator: (self.numerator * other.denominator - other.numerator * self.denominator),
            denominator: (self.denominator * other.denominator),
        }
    }
}

impl<'a> Mul for &'a Fraction {
    type Output = Fraction;

    fn mul(self, other: Self) -> Fraction {
        Fraction {
            numerator: (self.numerator * other.numerator),
            denominator: (self.denominator * other.denominator),
        }
    }
}

impl<'a> Div for &'a Fraction {
    type Output = Fraction;

    fn div(self, other: Self) -> Fraction {
        Fraction {
            numerator: (self.numerator * other.denominator),
            denominator: (self.denominator * other.numerator),
        }
    }
}

// Calculate the greatest common denominator for two numbers
pub fn gcd(a: i128, b: i128) -> i128 {
    if a == 0 || b == 0 {
        return max(a, b);
    }
    return gcd(max(a, b) % min(a, b), min(a, b));
}

pub fn topological_sort (adj: Vec<Vec<usize>>) -> Vec<usize> {
    let mut in_degree = vec![0; adj.len()];
    let mut queue: VecDeque<usize> = VecDeque::new();
    for i in 0..adj.len() {
        for j in adj[i].iter() {
            in_degree[*j] += 1;
        }
    }
    for i in 0..adj.len() {
        if in_degree[i] == 0 {
            queue.push_back(i);
        }
    }
    let mut ans = Vec::new();
    while ! queue.is_empty() {
        let x = queue[0];
        ans.push(x);
        queue.pop_front();
        for i in adj[x].iter() {
            in_degree[*i] -= 1;
            if in_degree[*i] == 0 {
                queue.push_back(*i);
            }
        }
    }
    return ans;
}

fn main() {
    let mut scan = Scanner::default();
    let n = scan.next::<usize>();
    let m = scan.next::<usize>();
    let mut adj: Vec<Vec<usize>> = Vec::new();
    for _ in 0..n {
        let mut x: usize = scan.next::<usize>();
        let mut gamma = Vec::new();
        for _ in 0..x {
            gamma.push(scan.next::<usize>() - 1);
        }
        adj.push(gamma);
    }
    let mut val: Vec<Fraction> = vec![Fraction::new(0, 1); n];
    for i in 0..m {
        val[i] = Fraction{numerator: 1, denominator: 1};
    }
    for idk in topological_sort(adj.clone()).iter() {
        let top = *idk;
        for i in adj[top].iter() {
            let mut gamma = val[top].clone();
            gamma = &gamma / &Fraction{numerator: adj[top].len() as i128, denominator: 1};
            gamma.reduce();
            val[*i] = &val[*i] + &gamma;
            val[*i] = val[*i].reduce();
        }
        if !adj[top].is_empty() {
            val[top] = Fraction::new(0, 1);
        }
    }
    for i in 0..adj.len() {
        if adj[i].is_empty() {
            println!("{} {}", val[i].numerator, val[i].denominator);
        }
    }
}
