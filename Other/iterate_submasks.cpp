//подмаски
for (int mask = 0; mask < (1 << n); ++mask) {
  for (int s = mask; s; s = (s - 1)&mask) {
    //proceed s;		
  }
}

//надмаски
for (int mask = 0; mask < (1 << n); ++mask) {
		int inversion = (1 << n) - 1 & ~mask;
		//proceed mask first
		for (int s = inversion; s; s = (s - 1)&inversion) {
			int cur_mask = s ^ mask;
			//proceed cur_mask
		}
	}
