#include "supertriangles.h"

void supertriangles(Partition *partition, int hilbertDimension)
{
#if NO_DIM == 2
    supertriangles2D(partition, hilbertDimension);
#elif NO_DIM == 3
    supertriangles3D(partition, hilbertDimension);
#else
    supertriangles4DAndMore(partition, hilbertDimension);
#endif
}

#if NO_DIM == 2
void supertriangles2D(Partition *partition, int hilbertDimension)
{
    // PointId *point1 = (PointId *)malloc(sizeof(PointId));
    // PointId *point2 = (PointId *)malloc(sizeof(PointId));
    // PointId *point3 = (PointId *)malloc(sizeof(PointId));
    // PointId *point4 = (PointId *)malloc(sizeof(PointId));

    // point1->point.x = 0;
    // point1->point.y = 0;

    // point2->point.x = 100;
    // point2->point.y = 0;

    // point3->point.x = 0;
    // point3->point.y = 100;

    // point4->point.x = 100;
    // point4->point.y = 100;

    PointId *point1 = newPointId(0, 0);
    PointId *point2 = newPointId(100, 0);
    PointId *point3 = newPointId(0, 100);
    PointId *point4 = newPointId(100, 100);

    PointId *triangle1Points[3] = {point1, point2, point3};
    Simplex *triangle1 = (Simplex *)malloc(sizeof(Simplex));
    createNewSimplex(triangle1, triangle1Points, hilbertDimension);

    PointId *triangle2Points[3] = {point2, point3, point4};
    Simplex *triangle2 = (Simplex *)malloc(sizeof(Simplex));
    createNewSimplex(triangle2, triangle2Points, hilbertDimension);

    for (int i = 0; i < 3; i++)
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
#endif

#if NO_DIM == 3
void supertriangles3D(Partition *partition, int hilbertDimension)
{
    // printf("1\n");
    int n = (int)pow(2, NO_DIM);
    // printf("2\n");
    PointId **points = (PointId **)malloc(n * sizeof(PointId *));
    // printf("3\n");

    // printf("Points: %p\n", points);

    for (int i = 0; i < n; i++)
    {
        points[i] = (PointId *)malloc(sizeof(PointId));
        points[i] = newPointId(i % 2 == 0 ? 0 : 100, (i / 2) % 2 == 0 ? 0 : 100, (i / 4) % 2 == 0 ? 0 : 100);
        // points[i]->point.x = i%2 == 0 ? 0 : 100;
        // points[i]->point.y = (i/2)%2 == 0 ? 0 : 100;
        // points[i]->point.z = (i/4)%2 == 0 ? 0 : 100;
    }

#if DEBUG_TRIANGULATION
    for (int i = 0; i < n; i++)
    {
        // printf("Point %i: x: %f, y: %f, z: %f \n", i, points[i]->point.x, points[i]->point.y, points[i]->point.z);
        printf("%s\n", printLongPointId(points[i]));
    }
#endif

    // Number of triangles
    int m = 5;
    PointId ***trianglePoints = (PointId ***)malloc(m * sizeof(PointId **));

    trianglePoints[0] = (PointId **)malloc((NO_DIM + 1) * sizeof(PointId *));
    trianglePoints[0][0] = points[0];
    trianglePoints[0][1] = points[1];
    trianglePoints[0][2] = points[2];
    trianglePoints[0][3] = points[4];

    trianglePoints[1] = (PointId **)malloc((NO_DIM + 1) * sizeof(PointId *));
    trianglePoints[1][0] = points[3];
    trianglePoints[1][1] = points[2];
    trianglePoints[1][2] = points[1];
    trianglePoints[1][3] = points[7];

    trianglePoints[2] = (PointId **)malloc((NO_DIM + 1) * sizeof(PointId *));
    trianglePoints[2][0] = points[6];
    trianglePoints[2][1] = points[4];
    trianglePoints[2][2] = points[2];
    trianglePoints[2][3] = points[7];

    trianglePoints[3] = (PointId **)malloc((NO_DIM + 1) * sizeof(PointId *));
    trianglePoints[3][0] = points[5];
    trianglePoints[3][1] = points[4];
    trianglePoints[3][2] = points[1];
    trianglePoints[3][3] = points[7];

    trianglePoints[4] = (PointId **)malloc((NO_DIM + 1) * sizeof(PointId *));
    trianglePoints[4][0] = points[4];
    trianglePoints[4][1] = points[1];
    trianglePoints[4][2] = points[7];
    trianglePoints[4][3] = points[2];

    Simplex **triangles = (Simplex **)malloc(m * sizeof(Simplex *));

    for (int i = 0; i < m; i++)
    {
        triangles[i] = (Simplex *)malloc(sizeof(Simplex));
        createNewSimplex(triangles[i], trianglePoints[i], hilbertDimension);

        // printf("Created new Simplex %14p, circumcenter: x: %10.4f, y: %10.4f, z: %10.4f, circumradius: %10.4f \n", triangles[i], triangles[i]->circumcenter.x, triangles[i]->circumcenter.y, triangles[i]->circumcenter.z, triangles[i]->circumradius);

        for (int j = 0; j < NO_DIM + 1; j++)
        {
            triangles[i]->neighbors[j] = NULL;
        }
    }

    for (int i = 0; i < m; i++)
    {
        triangles[i]->neighbors[0] = triangles[m - 1];
    }

    triangles[4]->neighbors[0] = triangles[1];
    triangles[4]->neighbors[1] = triangles[2];
    triangles[4]->neighbors[2] = triangles[0];
    triangles[4]->neighbors[3] = triangles[3];

    // printRedBlackTreeTriangles(partition->triangles);

    for (int i = 0; i < m; i++)
    {
        sortPointsInSimplex(triangles[i]);
        insertIntoRedBlackTree(partition->triangles, triangles[i]);

        // printRedBlackTreeTriangles(partition->triangles);
    }

#if DEBUG_TRIANGULATION
    printRedBlackTreeString(partition->triangles, printShortSimplex);
#endif
    // printf("1\n");
}
#endif

#if NO_DIM > 3
void supertriangles4DAndMore(Partition *partition, int hilbertDimension)
{
    fprintf(stderr, "Error in %s line %i: supertriangles4DAndMore function is not implemented \n", (char *)__FILE__, __LINE__);
}
#endif
