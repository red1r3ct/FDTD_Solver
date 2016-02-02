#include "JobScheduler.h"

#include <thrust/for_each.h>

template <typename Functor, typename Iterator>
void syncRun(Policy policy, Iterator start, Iterator end, Functor functor) {
	if(policy == thrustPolicy) {
		thrust::for_each(start , end , functor);
	}
}
