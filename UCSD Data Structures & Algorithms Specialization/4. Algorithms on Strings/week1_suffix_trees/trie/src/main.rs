// #[allow(dead_code)]
// const MAX_PATTERNS: usize = 100;
// #[allow(dead_code)]
// const MAX_LENGTH: usize = 100;

use std::io::{self, BufRead};
use std::collections::HashMap;
use std::collections::hash_map::Entry;

type TrieType = HashMap<(u16, u8), u16>;                    // Map of (node, char) -> next node
// use std::time::Instant;

fn main() {
    let mut it = io::stdin().lock().lines();
    let n: usize = it.next().unwrap().unwrap().parse().unwrap();

    let mut patterns = Vec::with_capacity(n);
    for _ in 0..n {
        patterns.push(it.next().unwrap().unwrap());
    }

    // const ITER: usize = 1000000;
    // let start = Instant::now();

    // for _ in 0..ITER {
    let trie = TrieConstruct(&patterns);
    for (key, value) in trie {
        println!("{}->{}:{}", key.0, value, key.1 as char);
    }
    // }

    // let total = start.elapsed();

    // println!(
    //     "Average time: {:.10} seconds",
    //     total.as_secs_f64() / ITER as f64
    // );
}

#[allow(non_snake_case)]
fn TrieConstruct(patterns: &Vec<String>) -> TrieType {
    let mut trie: TrieType = HashMap::with_capacity(patterns[0].len());
    let mut new_node: u16 = 1;
    let mut key: (u16, u8) = (0, 0);

    for pattern in patterns {
        key.0 = 0;

        for c in pattern.as_bytes() {
            key.1 = *c;
            
            if let Entry::Vacant(e) = trie.entry(key) {
                e.insert(new_node);
                key.0 = new_node;
                new_node += 1;
            }
            else {
                key.0 = trie[&key];
            }
        }
    }

    trie
}