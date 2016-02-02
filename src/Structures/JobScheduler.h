/*
 * JobScheduler.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef JOBSCHEDULER_H_
#define JOBSCHEDULER_H_

// Должен выполнять нужные вычисления и инкапсулировать
// способ и устройство на котором происходят вычисления
// За модель потоков стоит взять boost::threads

enum Policy {thrustPolicy, cudaPolicy, ompPolicy};

/*template <typename Functor, typename Iterator>
class JobScheduler {
private:
	JobScheduler();
	JobScheduler(const JobScheduler&);
	JobScheduler& operator= (JobScheduler&);

	static JobScheduler * instance;

public:
	~JobScheduler();

	static JobScheduler* getInstance() {
		if( instance == nullptr ) {
			instance = new JobScheduler;
		}
		return instance;
	}
};*/

template <typename Functor, typename Iterator>
void syncRun(Policy policy, Iterator start, Iterator end, Functor functor);

#endif /* JOBSCHEDULER_H_ */
