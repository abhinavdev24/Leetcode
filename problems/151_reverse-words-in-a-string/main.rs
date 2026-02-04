struct Solution;

impl Solution {
    pub fn reverse_words(s: String) -> String {
        // TODO: implement
        let _ = s;
        String::new()
    }
}

fn main() {
    let sample1 = String::from("the sky is blue");
    let sample2 = String::from("  hello world  ");
    let sample3 = String::from("a good   example");

    let result1 = Solution::reverse_words(sample1);
    println!("Sample 1 placeholder result: \"{}\"", result1);
    println!("Sample 1 expected output: \"blue is sky the\"\n");

    let result2 = Solution::reverse_words(sample2);
    println!("Sample 2 placeholder result: \"{}\"", result2);
    println!("Sample 2 expected output: \"world hello\"\n");

    let result3 = Solution::reverse_words(sample3);
    println!("Sample 3 placeholder result: \"{}\"", result3);
    println!("Sample 3 expected output: \"example good a\"");
}
