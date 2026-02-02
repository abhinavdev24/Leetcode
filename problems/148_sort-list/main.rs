#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

struct Solution;

impl Solution {
    pub fn sort_list(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        if head.is_none() || head.as_ref().unwrap().next.is_none() {
            return head;
        }
        // find middle
        let mut slow = &mut head;
        let mut fast = &head;
        while fast.is_some() && fast.as_ref().unwrap().next.is_some() {
            slow = &mut slow.as_mut().unwrap().next;
            fast = &fast.as_ref().unwrap().next.as_ref().unwrap().next;
        }
        // now slow is the node before middle
        let mut right = slow.as_mut().unwrap().next.take();
        let left = Self::sort_list(head);
        let right = Self::sort_list(right);
        Self::merge(left, right)
    }

    fn merge(a: Option<Box<ListNode>>, b: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let mut dummy = Box::new(ListNode::new(0));
        let mut curr = &mut dummy;
        let mut a = a;
        let mut b = b;
        while a.is_some() && b.is_some() {
            if a.as_ref().unwrap().val < b.as_ref().unwrap().val {
                let next = a.as_mut().unwrap().next.take();
                curr.next = a;
                a = next;
            } else {
                let next = b.as_mut().unwrap().next.take();
                curr.next = b;
                b = next;
            }
            curr = curr.next.as_mut().unwrap();
        }
        if a.is_some() {
            curr.next = a;
        }
        if b.is_some() {
            curr.next = b;
        }
        dummy.next
    }
}

fn build_list(values: &[i32]) -> Option<Box<ListNode>> {
    let mut head: Option<Box<ListNode>> = None;
    for &v in values.iter().rev() {
        let mut node = Box::new(ListNode::new(v));
        node.next = head;
        head = Some(node);
    }
    head
}

fn list_to_vec(mut head: Option<Box<ListNode>>) -> Vec<i32> {
    let mut out = Vec::new();
    while let Some(node) = head {
        out.push(node.val);
        head = node.next;
    }
    out
}

fn main() {
    let samples = vec![
        (vec![4, 2, 1, 3], vec![1, 2, 3, 4]),
        (vec![-1, 5, 3, 4, 0], vec![-1, 0, 3, 4, 5]),
        (vec![], vec![]),
    ];

    for (idx, (input, expected)) in samples.into_iter().enumerate() {
        let head = build_list(&input);
        let result_head = Solution::sort_list(head);
        let result = list_to_vec(result_head);

        println!("Sample {}: head = {:?}", idx + 1, input);
        println!("Placeholder result: {:?}", result);
        println!("Expected output: {:?}\\n", expected);
    }
}
