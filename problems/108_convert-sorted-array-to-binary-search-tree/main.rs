#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Box<TreeNode>>,
    pub right: Option<Box<TreeNode>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

struct Solution;

impl Solution {
    pub fn sorted_array_to_bst(nums: Vec<i32>) -> Option<Box<TreeNode>> {
        fn build(nums: &Vec<i32>, l: usize, r: usize) -> Option<Box<TreeNode>> {
            if l > r {
                return None;
            }
            let mid = l + (r - l) / 2;
            let mut root = Box::new(TreeNode::new(nums[mid]));
            if mid > 0 {
                root.left = build(nums, l, mid - 1);
            }
            root.right = build(nums, mid + 1, r);
            Some(root)
        }

        if nums.is_empty() {
            return None;
        }
        build(&nums, 0, nums.len() - 1)
    }
}

fn preorder_with_nulls(root: &Option<Box<TreeNode>>, out: &mut Vec<String>) {
    match root {
        Some(node) => {
            out.push(node.val.to_string());
            preorder_with_nulls(&node.left, out);
            preorder_with_nulls(&node.right, out);
        }
        None => out.push("null".to_string()),
    }
}

fn main() {
    let samples = vec![
        (
            vec![-10, -3, 0, 5, 9],
            "[0,-3,9,-10,null,5] or [0,-10,5,null,-3,null,9]",
        ),
        (vec![1, 3], "[3,1] or [1,null,3]"),
    ];

    for (idx, (nums, expected)) in samples.into_iter().enumerate() {
        let result = Solution::sorted_array_to_bst(nums.clone());
        let mut traversal = Vec::new();
        preorder_with_nulls(&result, &mut traversal);

        println!("Sample {}: nums = {:?}", idx + 1, nums);
        println!(
            "Placeholder result (preorder with nulls): {}",
            traversal.join(",")
        );
        println!("Expected output: {}\\n", expected);
    }
}
