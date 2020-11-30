#include "supertriangles.h"

void supertriangles(Partition *partition)
{
#if NO_DIM == 2
    supertriangles2D(partition);
#elif NO_DIM == 3
    supertriangles3D(partition);
#else
    supertriangles4DAndMore(partition);
#endif
}

void supertriangles2D(Partition *partition)
{
    PointId *point1 = (PointId *)malloc(sizeof(PointId));
    PointId *point2 = (PointId *)malloc(sizeof(PointId));
    PointId *point3 = (PointId *)malloc(sizeof(PointId));
    PointId *point4 = (PointId *)malloc(sizeof(PointId));

    point1->point.x = 0;
    point1->point.y = 0;

    point2->point.x = 100;
    point2->point.y = 0;

    point3->point.x = 0;
    point3->point.y = 100;

    point4->point.x = 100;
    point4->point.y = 100;

    PointId triangle1Points[3] = {*point1, *point2, *point3};
    Simplex *triangle1 = (Simplex *)malloc(sizeof(Simplex));
    createNewSimplex(triangle1, triangle1Points);

    PointId triangle2Points[3] = {*point2, *point3, *point4};
    Simplex *triangle2 = (Simplex *)malloc(sizeof(Simplex));
    createNewSimplex(triangle2, triangle2Points);

    for(int i = 0; i < 3; i++)
    {
        triangle1->neighbors[i] = NULL;
        triangle2->neighbors[i] = NULL;
    }

    triangle1->neighbors[0] = triangle2;
    triangle2->neighbors[2] = triangle1;

    sortPointsInSimplex(triangle1);
    sortPointsInSimplex(triangle2);

    // printRedBlackTree(partition->triangles);

    insertIntoRedBlackTree(partition->triangles, triangle1);

    // printRedBlackTree(partition->triangles);

    insertIntoRedBlackTree(partition->triangles, triangle2);

    // printRedBlackTree(partition->triangles);

    insertIntoRedBlackTree(partition->globalVertices, point1);
    insertIntoRedBlackTree(partition->globalVertices, point2);
    insertIntoRedBlackTree(partition->globalVertices, point3);
    insertIntoRedBlackTree(partition->globalVertices, point4);
}

#if NO_DIM == 3
void supertriangles3D(Partition *partition)
{
    int n = (int)pow(2, NO_DIM);
    PointId **points = (PointId**)malloc(n * sizeof(PointId*));

    for(int i = 0; i < n; i++)
    {
        points[i]->point.x = i%2 == 0 ? 0 : 100;
        points[i]->point.x = (i/2)%2 == 0 ? 0 : 100;
        points[i]->point.x = (i/4)%2 == 0 ? 0 : 100;
    }

    // Number of triangles
    int m = 5;
    PointId **trianglePoints = (PointId**)malloc(m * sizeof(PointId*));

    trianglePoints[0] = (PointId*)malloc((NO_DIM + 1) * sizeof(PointId));
    trianglePoints[0][0] = *points[0];
    trianglePoints[0][0] = *points[1];
    trianglePoints[0][0] = *points[2];
    trianglePoints[0][0] = *points[4];

    trianglePoints[1] = (PointId*)malloc((NO_DIM + 1) * sizeof(PointId));
    trianglePoints[1][0] = *points[1];
    trianglePoints[1][0] = *points[2];
    trianglePoints[1][0] = *points[3];
    trianglePoints[1][0] = *points[7];

    trianglePoints[2] = (PointId*)malloc((NO_DIM + 1) * sizeof(PointId));
    trianglePoints[2][0] = *points[6];
    trianglePoints[2][0] = *points[4];
    trianglePoints[2][0] = *points[2];
    trianglePoints[2][0] = *points[7];

    trianglePoints[3] = (PointId*)malloc((NO_DIM + 1) * sizeof(PointId));
    trianglePoints[3][0] = *points[5];
    trianglePoints[3][0] = *points[4];
    trianglePoints[3][0] = *points[1];
    trianglePoints[3][0] = *points[7];

    trianglePoints[4] = (PointId*)malloc((NO_DIM + 1) * sizeof(PointId));
    trianglePoints[4][0] = *points[4];
    trianglePoints[4][0] = *points[1];
    trianglePoints[4][0] = *points[7];
    trianglePoints[4][0] = *points[2];

    Simplex **triangles = (Simplex**)malloc(m * sizeof(Simplex*));
    
    for(int i = 0; i < m; i++)
    {
        triangles[i] = (Simplex*)malloc(sizeof(Simplex));
        createNewSimplex(triangles[i], trianglePoints[i]);
        
        for(int j = 0; j < NO_DIM + 1; j++)
        {
            triangles[i]->neighbors[j] = NULL;
        }
    }

    for(int i = 0; i < m; i++)
    {
        triangles[i]->neighbors[0] = triangles[m - 1];
    }

    triangles[4]->neighbors[0] = 1; 
    triangles[4]->neighbors[1] = 2;
    triangles[4]->neighbors[2] = 0;
    triangles[4]->neighbors[3] = 3;

    for(int i = 0; i < m; i++)
    {
        sortPointsInSimplex(triangles[i]);
        insertIntoRedBlackTree(partition->triangles, triangles[i]);
    }
}
#endif

#if NO_DIM > 3
void supertriangles4DAndMore(Partition *partition)
{
    fprintf(stderr, "Error in %s line %i: supertriangles4DAndMore function is not implemented \n", (char *)__FILE__, __LINE__);
}
#endif
