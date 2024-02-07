#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// shellSort 将数组分组，并不断减小分组的步长直到为1，每次分组均进行插入排序
/*
算法引入原因：
  希尔排序是插入排序的一种改进。
  因为对于插入排序而言，如果满足以下两点，效率很高
    1. 待排序的序列基本有序。
    2. 待排序的序列元素较少时。
  注：
    基本有序是指已经接近正序。如：1、2、7、4、5、6、3、8
    局部有序是指某些部分有序。如：6、7、8、1、2、3、4、5
    
算法思想：
  针对插入排序高效条件的第2点，我们可以将整个待排序的序列分割成若干个子序列，然后对这些子序列进行插入排序。
  因为子序列数据量较小，所以这个时候插入的效率较高。
  待整个序列基本有序的时候（即插入排序高效的第1点），再对整个序列进行一次插入排序即可。
  
  注：  
    1. 子序列的分割不能是简单的 "逐段分割"，而是将相距某个增量的元素组成一个子序列。
    这样才能保证在子序列中进行插入排序后，是基本有序，而非局部有序。
    （增量一般初始化为：序列长度的一半，每次减半，直到最后一个增量为1）
*/
void shellSort(vector<int>& nums) {
    int N = nums.size();
    int d, i, j, tmp;
    for(d = N/2; d >= 1; d = d/2) {     // 控制增量的循环。增量的初始值为原序列的一半。增量为 d 进行插入排序
        for(i = d; i < N; i++) {        // 进行一趟希尔排序
            tmp = nums[i];
            for(j = i-d; j >= 0 && tmp < nums[j]; j = j-d) {    // 注意：这里 i-1 变为了i-d
                nums[j+d] = nums[j];    // 注：j+1 变为了 j+d
            }
            nums[j+d] = tmp;            // 注：j+1 变为了 j+d
        }
    }
}
/*
复杂度分析：
    时间复杂度：O(n*log(n))-O(n^2)之间，选择合适的增量序列，可以达到n^1.3。但是一般都是用最坏时间复杂度，所以为O(n^2)
    空间复杂度：O(1)
    
稳定性：
  不稳定。因为希尔排序涉及多次交换和比较，通常会破坏相等元素的相对顺序，所以它是不稳定的排序算法。
  （虽然插入排序是稳定的，但是希尔排序在插入的时候是跳跃性插入的，有可能破坏稳定性）

注意：
  希尔排序的时间复杂度难以精确确定，因为它的性能取决于所选的增量序列。
  在大多数情况下，现代排序算法（如快速排序或归并排序）更具性能优势。
  希尔排序的主要优点在于它的原地排序性质（in-place），因此对于内存受限的情况可能有用。
*/
/******************************测试程序如下*******************************/
int main() {
    vector<int> tmp = {9, 3, 6, 1, 8, 5, 2, 7, 4};
    for_each(begin(tmp), end(tmp), [](int a) { cout << a << " "; });
    cout << endl;

    shellSort(tmp);
    for_each(begin(tmp), end(tmp), [](int a) { cout << a << " "; });
    cout << endl;
    return 0;
}