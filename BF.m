src = 1;
dist = inf(1,n);
dist(src)=0;
for i=1:n-1
     for j=1:n
       for k=1:n
         if adj(j,k) != 0
            if dist(j)+adj(j,k)<dist(k)
               dist(k)=dist(j)+adj(j,k);
           end
         end
       end
     end
  end
disp(dist);
