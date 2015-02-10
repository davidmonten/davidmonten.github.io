mirror([1,1,0]){
polyhedron(
  points=[ [10,5,0],[3,-10,0],[-10,-7,0],[-10,10,0],    // the four points at base
           [6,5,10]  ],                                 // the apex point 
  faces=[ [0,1,4],[1,2,4],[2,3,4],[3,0,4],              // each triangle side
              [1,0,3],[2,1,3] ]                         // two triangles for square base
 );
};
!polyhedron(
  points=[ [10,5,0],[3,-10,0],[-10,-7,0],[-10,10,0],    // the four points at base
           [6,5,10]  ],                                 // the apex point 
  faces=[ [0,1,4],[4,2,1],[2,3,4],[3,0,4],              // each triangle side
                                                        // DUE TO THE ORDER OF VERTEX
                                                        // THE SECOND FACE IS FLIPPED
                                                        // AND THE NORMAL VECTOR IS
                                                        // POINTING INWARD.
              [1,0,3],[2,1,3] ]                         // two triangles for square base
 );