
void swap(int* i, int* j){
	int tmp = *i;
	*i = *j;
	*j = tmp;
}

int Partition(int array[], int low, int high){
	// 采用子序列的第一个元素为枢纽元素
	int pivot = array[low];
	while (low < high){
		// 从后往前在后半部分中寻找第一个小于枢纽元素的元素
		while (low < high && array[high] >= pivot){
			--high;
		}
		// 将这个比枢纽元素小的元素交换到前半部分
		swap(&array[low], &array[high]);
		// 从前往后在前半部分中寻找第一个大于枢纽元素的元素
		while (low < high && array[low] <= pivot)
		{
			++low;
		}
		// 将这个比枢纽元素大的元素交换到后半部分
		swap(&array[low], &array[high]);
	}
	// 返回枢纽元素所在的位置
	return low;
}
// 快速排序
void QuickSort(int array[], int low, int high){
	if (low < high)
	{
		int n = Partition(array, low, high);
		QuickSort(array, low, n);
		QuickSort(array, n + 1, high);
	}
}
