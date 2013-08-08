// pthread_cond,生产者、消费者模型
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct msg
{
	struct msg *next;
	int num;
};

struct msg		*head;
pthread_cond_t	 has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t	 lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p)
{
	struct msg *mp;

	for(;;)
	{
		pthread_mutex_lock(&lock);
		while(head == NULL)
		{
			pthread_cond_wait(&has_product, &lock);
			// 线程调用pthread_cond_wait在一个Condition Variable上
			// 阻塞等待，这个函数做以下三步操作：
			// 1. 释放Mutex
			// 2. 阻塞等待
			// 3. 当被唤醒时，重新获得Mutex并返回 
		}
		mp = head;
		head = mp->next;
		pthread_mutex_unlock(&lock);

		printf("Consume -%d\n", mp->num);
		free(mp);
		sleep(rand() % 5);
	}

	return NULL;
}

void *producer(void *p)
{
	struct msg *mp;

	for(;;)
	{
		mp = (msg *) malloc(sizeof(struct msg));
		mp->num = rand() % 1000 + 1;
		printf("Produce +%d\n", mp->num);

		pthread_mutex_lock(&lock);
		mp->next = head;
		head = mp;
		pthread_mutex_unlock(&lock);

		pthread_cond_signal(&has_product);
		// 线程可以调用pthread_cond_signal唤醒在
		// 某个Condition Variable上等待的另一个线程
		sleep(rand() % 5);
	}
}

int main()
{
	pthread_t pid, cid, cid1;

	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&cid, NULL, consumer, NULL);
	pthread_create(&cid1, NULL, consumer, NULL);

	pthread_join(pid, NULL);
	pthread_join(cid, NULL);
	pthread_join(cid1, NULL);

	return 0;
}

