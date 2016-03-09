#if defined _inc_sort_inline
  #endinput
#endif
#define _inc_sort_inline

#define MergeSort%0(%1); \
	{ new _buf[sizeof(%1)]; MergeSortImpl(%1, _, _buf); }

stock MergeSortImpl(arr[], size = sizeof(arr), buf[])
{
	if (size < 2) {
		return;
	}
	
	new mid = size / 2;
	
	MergeSortImpl(arr, mid, buf);
	MergeSortImpl(arr[mid], size - mid, buf[mid]);
	
	for (new i = 0; i < size; i++) {
		buf[i] = arr[i];
	}
	
	for (new i, j, k = mid; i < size; i++) {
		if (k >= size) {
			arr[i] = buf[j++];
		} else if (j >= mid) {
			arr[i] = buf[k++];
		} else if (buf[j] > buf[k]) {
			arr[i] = buf[j++];
		} else {
			arr[i] = buf[k++];
		}
	}
}

#define MergeSortBU%0(%1); \
	{ new _buf[sizeof(%1)]; MergeSortBUImpl(%1, _, _buf); }

stock MergeSortBUImpl(arr[], size = sizeof(arr), buf[], &initial = true, &sz, &lo, &mid, &hi, &i, &j, &k, &left, &right, &bool:r)
{
	static const T = true;
	
	if (!initial) {
		goto comparison_done;
	}
	
	initial = false;
	
	for (sz = 1; sz < size; sz += sz) {
		for (lo = 0; lo < size - sz; lo += sz * 2) {
			mid = lo + sz - 1;
			hi = min(lo + sz * 2 - 1, size - 1);
			
			if (hi - lo < 1) {
				continue;
			}
			
			for (new n = lo; n <= hi; n++) {
				buf[n] = arr[n];
			}

			for (i = lo, j = lo, k = mid + 1; i <= hi; i++) {
				if (k > hi) {
					arr[i] = buf[j++];
				} else if (j > mid) {
					arr[i] = buf[k++];
				} else {
					left = buf[j];
					right = buf[k];
					if (T) {
						return true;
					}
comparison_done:
					if (r) {
						arr[i] = buf[j++];
					} else {
						arr[i] = buf[k++];
					}
				}
			}
		}
	}
	
	return false;
}

#define sortInline%1=>%0(%2=%3>%4) \
	for ( \
		new _buf[sizeof(%1)], _initial = true, _sz, _lo, _mid, _hi, _i, _j, _k, %3, %4, bool:%2; \
		MergeSortBUImpl(_:%1, sizeof(%1), _buf, _initial, _sz, _lo, _mid, _hi, _i, _j, _k, _:%3, _:%4, %2); \
	)

#define sortPartInline%1%0(%5)=>%0(%2=%3>%4) \
	for ( \
		new _buf[sizeof(%1)], _initial = true, _sz, _lo, _mid, _hi, _i, _j, _k, %3, %4, bool:%2; \
		MergeSortBUImpl(_:%1, %5, _buf, _initial, _sz, _lo, _mid, _hi, _i, _j, _k, _:%3, _:%4, %2); \
	)
