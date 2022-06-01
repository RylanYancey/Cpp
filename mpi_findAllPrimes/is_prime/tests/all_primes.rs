
use std::{
    io::{
        Write,
    },
    fs::{
        File,
    },
    time::{
        SystemTime,
    }
};

const TARGET: i32 = 1000000;

#[test]
fn test() {

    let path = "rust_primes.txt";

    let mut output = File::create(path).unwrap();

    let t1 = SystemTime::now();

    for x in 0..TARGET {
        if is_prime(x) {
            write!(output, "{} ", x).unwrap();
        }
    }

    println!("time: {}", t1.elapsed().unwrap().as_millis() as f32 * 0.001);

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