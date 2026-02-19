struct Solution;

impl Solution {
    pub fn reverse_words(s: String) -> String {
        let bytes = s.as_bytes();
        let mut i: isize = bytes.len() as isize - 1;
        let mut result = String::new();

        while i >= 0 {
            // skip trailing spaces
            while i >= 0 && bytes[i as usize] == b' ' {
                i -= 1;
            }

            if i < 0 {
                break;
            }

            let mut j = i;
            // find start of the word
            while j >= 0 && bytes[j as usize] != b' ' {
                j -= 1;
            }

            // append word
            if !result.is_empty() {
                result.push(' ');
            }
            let start = (j + 1) as usize;
            let end = (i + 1) as usize; // exclusive
            result.push_str(&s[start..end]);

            i = j - 1;
        }

        result
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
