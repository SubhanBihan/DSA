#[allow(dead_code)]
const MAX_PATTERNS: usize = 100;
#[allow(dead_code)]
const MAX_LENGTH: usize = 100;

use std::io::{self, BufRead};
use std::collections::HashMap;

fn main() {
    let mut it = io::stdin().lock().lines();
    let n: usize = it.next().unwrap().unwrap().parse().unwrap();

    let mut patterns = Vec::with_capacity(n);
    for _ in 0..n {
        patterns.push(it.next().unwrap().unwrap());
    }

    let edges = Trie(&patterns);
    for e in &edges {
        println!("{e}");
    }
}

fn Trie(patterns: &Vec<String>) -> Vec<String> {
    let mut trie: Vec<HashMap<u8, u16>> = Vec::with_capacity(MAX_LENGTH);
    let mut edges: Vec<String> = Vec::with_capacity(patterns[0].len());

    let mut node: u16 = 1;
    let mut in_trie: bool;

    for pattern in patterns {
        in_trie = true;

        for i in 0..pattern.len() {
            if i >= trie.len() {
                trie.push(HashMap::new());
            }

            if !in_trie || !trie[i].contains_key(&pattern.as_bytes()[i]) {
                trie[i].insert(pattern.as_bytes()[i], node);
                
                let prev_node = if i == 0 {0} else {trie[i - 1][&pattern.as_bytes()[i - 1]]};

                edges.push(format!(
                    "{prev_node}->{node}:{}", pattern.as_bytes()[i] as char
                ));

                node += 1;
                in_trie = false;
            }
        }
    }

    edges
}