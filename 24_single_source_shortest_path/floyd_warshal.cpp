Floyd-Warshal
DP approach to find distances between nodes

for k = 1 ... n
   for i = 1 ... n
      for j = 1 ...n
         if c[i,j] > c[i,k] + c[k,j]
            c[i,j] = c[i,k] + c[k,j]
