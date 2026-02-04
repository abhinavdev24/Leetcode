struct Solution;

impl Solution {
    pub fn group_anagrams(strs: Vec<String>) -> Vec<Vec<String>> {
        use std::collections::HashMap;
        let mut mp: HashMap<String, Vec<String>> = HashMap::new();
        for s in strs {
            let mut sorted: Vec<char> = s.chars().collect();
            sorted.sort();
            let key = sorted.into_iter().collect::<String>();
            mp.entry(key).or_insert(Vec::new()).push(s);
        }
        mp.into_iter().map(|(_, v)| v).collect()
    }
}

fn main() {
    let sample1 = vec!["eat", "tea", "tan", "ate", "nat", "bat"]
        .into_iter()
        .map(String::from)
        .collect::<Vec<String>>();
    let sample2 = vec![""]
        .into_iter()
        .map(String::from)
        .collect::<Vec<String>>();
    let sample3 = vec!["a"]
        .into_iter()
        .map(String::from)
        .collect::<Vec<String>>();

    let result1 = Solution::group_anagrams(sample1);
    println!("Sample 1 placeholder result: {:?}", result1);
    println!("Sample 1 expected output: [[\"bat\"],[\"nat\",\"tan\"],[\"ate\",\"eat\",\"tea\"]]\n");

    let result2 = Solution::group_anagrams(sample2);
    println!("Sample 2 placeholder result: {:?}", result2);
    println!("Sample 2 expected output: [[\"\"]]\n");

    let result3 = Solution::group_anagrams(sample3);
    println!("Sample 3 placeholder result: {:?}", result3);
    println!("Sample 3 expected output: [[\"a\"]]");
}
