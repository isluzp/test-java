/*************************************************************************
    > File Name: epf.cpp
    > Author: luzhiping
    > Mail: isluzp@gmail.com 
    > Created Time: 2013年07月11日 星期四 13时22分11秒
	> 获取期望概率值以及经验期望，用法见本文件最下方demo
 ************************************************************************/
//#define _DEBUG_
#define _EPF_CPP_DEBUG_

#include <cstdio>
#include <cstdlib>
#include <math.h>

typedef struct _sample_t{
	int						val;   /** 值 */
	int						num;   /** 个数 */
	_sample_t*				next;
}sample_t;

void swap(int* i, int* j){
	int tmp = *i;
	*i = *j;
	*j = tmp;
}

int partition(int array[], int low, int high){
	int pivot = array[low];
	while (low < high){
		while (low < high && array[high] >= pivot){
			--high;
		}
		swap(&array[low], &array[high]);
		while (low < high && array[low] <= pivot)
		{
			++low;
		}
		swap(&array[low], &array[high]);
	}
	return low;
}

// 快速排序
void quick_sort(int *array, int low, int high){
	if (low < high)
	{
		int n = partition(array, low, high);
		quick_sort(array, low, n);
		quick_sort(array, n + 1, high);
	}
}

sample_t* init(int *X, int len){
	int val,num;
	sample_t *head = new sample_t;
	sample_t *p = head;
	quick_sort(X, 0, len-1 );
	val = X[0];
	num = 1;
	for(int i = 1; i < len; i++){
		if(X[i] == val && i != len-1){
			num++;
		}else{
			if(X[i] == val && len-1 == i) {
				p->val = val;
				p->num = ++num;
				break;
			}
			p->val = val;
			p->num = num;
			sample_t *sample = new sample_t;
			p->next = sample;
			p = sample;
			if(len-1 == i && X[i] != val){
				p->val = X[i];
				p->num = 1;
				break;
			}
			val = X[i];
			num = 1;
		}
	}
	p = NULL;
#ifdef _DEBUG_
	p = head;
	while(p != NULL){
		printf("line : %d  val : %d  num : %d  len(X) : %d\n",__LINE__, p->val, p->num, len);
		p = p->next;
	}
#endif //..
	return head;
}

/** delete new 出来的链表， 需要的时候补
void delete_linklist(){
    while(q !=NULL){
		k += q->num;
		q = q->next;
	}

}
*/
//函数的限制条件
float function(float x, float y){
	return x*y;
}

#define _DEBUG_
//#define F(x,y) function(x,y)

/**  获取期望概率值
 *	 当x,y相互独立时 p(x) * p(y|x) = p(x) * p(y)
 */
float expected_probability_value(sample_t *X, sample_t *Y){
	int i = 0, j = 0, k = 0;
	sample_t *p = X, *q = Y;
	while(p != NULL){
		j += p->num;
		while(q != NULL){
			i += p->num * q->num * function(p->val, q->val);
			q = q->next;
		}
		q = Y;
		p = p->next;
	}
	while(q !=NULL){
		k += q->num;
		q = q->next;
	}
#ifdef _DEBUG_
	printf("line :%d  i %d, k %d, j %d\n", __LINE__, i, k, j);
#endif //...
	return (float)i/(j*k);
}

float experience(sample_t *X, sample_t *Y){
		
}


#ifdef _EPF_CPP_DEBUG_
// demo
int main(){
	int i[9] = {1,2,3,4,5,6,7,8,9};
	int j[6] = {2,2,2,2,2,2};
	sample_t *spj = init(j, 2);
	sample_t *spi = init(i, 2);
	float result = expected_probability_value(spi,spj);
	printf("line :%d   %f  \n", __LINE__, result);
	return 0;
}
#endif //..

