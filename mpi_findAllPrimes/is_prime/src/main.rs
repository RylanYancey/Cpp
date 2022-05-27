
use std::fs;

/*
    Rust code for checking if primes.txt has all the promised primes.
    Also makes sure there are no mistakes. 
*/

fn main() {

    let contents = fs::read_to_string("../primes.txt").expect("Error");

    let mut unknown: Vec<i32> = Vec::new();

    println!("Move all primes into unknown");
    for line in contents.lines() {
        unknown.push(line.parse::<i32>().unwrap());
    }

    println!("Sort the primes");
    unknown.sort_unstable();

    println!("Generate the primes");
    let mut known: Vec<i32> = Vec::new();
    gen_primes(&mut known);

    println!("{} {}", unknown.len(), known.len());

    println!("Compare the primes");
    for (x, y) in unknown.iter().zip(known) {
        if x != &y {
            println!("Not matching!: {} {}", x, y);
            break;
        }
    }

}

pub fn gen_primes(known_good: &mut Vec<i32>) {

    let target = 1000000;

    known_good.push(1);
    known_good.push(2);

    let mut i = 3;

    while i < target {
        if is_prime(i) {
            known_good.push(i);
        }
        i += 2;
    }

}

pub fn is_prime(n: i32) -> bool {
    let mut i: i32 = 3;
    while i < n {
        if n % i == 0 {
            return false;
        }
        i += 1;
    }

    true
}