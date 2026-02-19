struct Solution;

impl Solution {
    pub fn num_decodings(s: String) -> i32 {
        if s.is_empty() {
            return 0;
        }
        let bytes = s.as_bytes();
        if bytes[0] == b'0' {
            return 0;
        }

        let mut prev: i32 = 1; // dp[i-2]
        let mut curr: i32 = 1; // dp[i-1]

        for i in 1..bytes.len() {
            let mut next: i32 = 0;

            // single-digit decode (non-zero)
            if bytes[i] != b'0' {
                next += curr;
            }

            // two-digit decode (10..26)
            if bytes[i - 1] == b'1' || (bytes[i - 1] == b'2' && bytes[i] <= b'6') {
                next += prev;
            }

            prev = curr;
            curr = next;
        }

        curr
    }
}

fn main() {
    let samples: Vec<(&str, i32)> = vec![("12", 2), ("226", 3), ("06", 0)];

    for (idx, (s, expected)) in samples.iter().enumerate() {
        let result = Solution::num_decodings((*s).to_string());
        println!(
            "Example {} result: {}, expected: {}",
            idx + 1,
            result,
            expected
        );
    }
}
