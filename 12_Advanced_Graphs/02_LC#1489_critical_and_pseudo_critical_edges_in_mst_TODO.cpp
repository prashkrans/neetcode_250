/* LC#1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree

Hints:
1. Use the Kruskal algorithm to find the minimum spanning tree by sorting 
the edges and picking edges from ones with smaller weights.

2. To find if one edge is critical, delete that edge and re-run the MST algorithm 
and see if the weight of the new MST increases.

3. To find if one edge is non-critical (in any MST), include that edge to the accepted 
edge list and continue the MST algorithm, then see if the resulting MST has the same weight 
of the initial MST of the entire graph.

*/