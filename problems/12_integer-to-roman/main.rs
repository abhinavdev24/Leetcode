struct Solution;

impl Solution {
    pub fn int_to_roman(mut num: i32) -> String {
        let roman_symbols = [
            "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I",
        ];
        let values = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1];
        let mut ans = String::new();
        for i in 0..13 {
            while num >= values[i] {
                ans.push_str(roman_symbols[i]);
                num -= values[i];
            }
        }
        ans
    }
}

fn main() {
    let sample1 = 3749;
    let sample2 = 58;
    let sample3 = 1994;

    let result1 = Solution::int_to_roman(sample1);
    println!("Sample 1 placeholder result: \"{}\"", result1);
    println!("Sample 1 expected output: \"MMMDCCXLIX\"\n");

    let result2 = Solution::int_to_roman(sample2);
    println!("Sample 2 placeholder result: \"{}\"", result2);
    println!("Sample 2 expected output: \"LVIII\"\n");

    let result3 = Solution::int_to_roman(sample3);
    println!("Sample 3 placeholder result: \"{}\"", result3);
    println!("Sample 3 expected output: \"MCMXCIV\"");
}
