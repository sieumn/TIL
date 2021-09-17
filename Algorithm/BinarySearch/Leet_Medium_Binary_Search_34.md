# [Leetcode] 34. Find First and Last Position of Element in Sorted Array

## 문제

https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

- input: 오름차순 정렬된 정수형 배열 nums, 정수 target
- output: 주어진 배열에서 target이 위치한 처음과 끝 index를 정수 배열으로 반환
- constraint: 시간 복잡도 O(log n) 내로 작성

## 알고리즘

### 이진 탐색

O(log n)의 시간 복잡도로 코드를 작성해야 했기 때문에 Divide and Conquer 방식으로 이진 탐색을 구현했다.

target에 해당되는 index가 여러개 있을 수 있기 때문에, target 하나 찾더라도 좌우에 target 값이 얼마나 더 있는지 확인하는 과정이 필요했다. 이렇게 접근하면 코드가 복잡하고 비효율적이 될 것 같아, target 값을 갖는 가장 작은 index를 찾는 searchLeft 함수와 target 값을 갖는 가장 오른쪽 index를 찾는 searchRight 함수를 따로 구현했다.

### 시간 복잡도

Divide and conquer 방식을 사용할 경우, 탐색을 반복할 때마다 탐색 대상이 1/2 씩 줄어든다. 따라서 각 searchLeft(), searchRight() 함수는 log n의 시간 복잡도를 갖고, 최종적으로 2*log n 의 시간 복잡도를 갖는 코드를 작성할 수 있다. 

## 최종 코드

```C++
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {        

        vector<int> index = {-1, -1};
        
        if(nums.size()==0) return index;
        
        if(nums[0]==target) index[0] = 0;
        else searchLeft(nums, 0, nums.size()-1, target, index);
        
        if(nums[nums.size()-1]==target) index[1] = nums.size()-1;
        else searchRight(nums, 0, nums.size()-1, target, index);
        
        return index;
    }
    
    static void searchLeft(vector<int>& nums, int first, int last, int target, vector<int>& index){

        if(first > last) return;
        
        else if(first == last){
            if(nums[first] == target) index[0] = first;
            return;
        }
        
        int middle = (first + last) / 2;
        if(nums[middle] < target)
            searchLeft(nums, middle+1, last, target, index);
        
        else if(nums[middle] > target)
            searchLeft(nums, first, middle-1, target, index);
        
        else{
            if(nums[middle-1] == target) searchLeft(nums, first, middle-1, target, index);
            else{
                index[0] = middle;
            }
        }

    }
    
    static void searchRight(vector<int>& nums, int first, int last, int target, vector<int>& index){
        
        if(first > last) return;
        
        else if(first == last){
            if(nums[first] == target) index[1] = last;
            return;
        }
        
        int middle = (first + last) / 2;
        if(nums[middle] < target)
            searchRight(nums, middle+1, last, target, index);
        
        else if(nums[middle] > target)
            searchRight(nums, first, middle-1, target, index);
        
        else{
            if(nums[middle+1] == target) searchRight(nums, middle+1, last, target, index);
            else{
                index[1] = middle;
            }
        }
        
    }
};
```