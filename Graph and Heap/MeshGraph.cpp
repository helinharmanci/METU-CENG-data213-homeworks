#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>
#include <float.h>

MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions, const std::vector<IdPair>& edges)
{
    // TODO:
    std::vector<int> visited;

    int edge_size=edges.size();
    visited.push_back((edges[0].vertexId0));
    visited.push_back((edges[0].vertexId1));
    int visited_size;
    for (int i=1; i< edge_size;i++)
    {
        bool push_0=true;
        bool push_1=true;
        visited_size=visited.size(); //su anda 2
        for (int j=0; j<visited_size; j++)
        {
            if(edges[i].vertexId0==visited[j]) //If IDPair's vertexID_0 is matching with the visited[j], I will not added it to the vertices vector, cause it's already added. So I make the flag push_0 false.
            {
                push_0=false;
            }
            if(edges[i].vertexId1==visited[j]) //If IDPair's vertexID_1 is matching with the visited[j], I will not added it to the vertices vector, cause it's already added. So I make the flag push_1 false.
            {
                push_1=false;
            }
        }
        if(push_0) //If edges[i]'s first vertex is not added to the vertices vector, I will push back
        {
            visited.push_back(edges[i].vertexId0);
        }
        if(push_1) //If edges[i]'s second vertex is not added to the vertices vector, I will push back
        {
            visited.push_back(edges[i].vertexId1);
        }
    }
    //visited vector has all vertices now. I'll add the vertices in the visited vector to the vertices vector
    visited_size=visited.size();
    for (int i=0;i<visited_size;i++)
    {
        Vertex temp;
        temp.id=0;
        vertices.push_back(temp);
    }
    for (int i=0;i<visited_size;i++)
    {
        int vertex_id=visited[i];
        vertices[vertex_id].id=visited[i];
    }

    int vertex_po_size=vertexPositions.size();
    for (int i=0;i<vertex_po_size;i++)
    {
        vertices[i].position3D=vertexPositions[i];
    }

    //vertices vector is done. Now it is time to deal with adjList vector
    int vertices_size=visited_size;

    for(int i=0;i<vertices_size;i++)
    {
        std::list<Vertex*> vertex_pointer;
        Vertex* vertex_to_be=&(vertices[i]);
        vertex_pointer.push_back(vertex_to_be); //example: I add the 0 now I'll add the 0's neighbours to the vertex_pointer list

        for (int j=0; j<edge_size;j++)
        {
            if (edges[j].vertexId0==i)
            {
                int neighbour_vertex_id=edges[j].vertexId1;
                Vertex* adj_vertex=&(vertices[neighbour_vertex_id]);
                vertex_pointer.push_back(adj_vertex);
            }
            else if(edges[j].vertexId1==i)
            {
                int neighbour_vertex_id=edges[j].vertexId0;
                Vertex* adj_vertex=&(vertices[neighbour_vertex_id]);
                vertex_pointer.push_back(adj_vertex);
            }
        }
        adjList.push_back(vertex_pointer);
    }
}

double MeshGraph::AverageDistanceBetweenVertices() const
{
    // TODO:
    //vertices'in içinde vertexler var. her vertex positionını tutuyor.
    int number_f_vertices=vertices.size();
    double sum=0;
    int edge_number=0;
    for(int i=0;i<number_f_vertices;i++)
    {
        double index_sum=0;
        std::list<Vertex*> temp=adjList[i];

        std::list<Vertex*>::const_iterator main = temp.begin();
        Double3 position_of_my_main= (*main)->position3D;
        std::list<Vertex*>::const_iterator a = temp.begin();
        for (; a != temp.end(); a++)
        {
            edge_number++;
            double x=(*a)->position3D.x;
            double y=(*a)->position3D.y;
            double z=(*a)->position3D.z;
            index_sum+= sqrt((position_of_my_main.x-x)*(position_of_my_main.x-x)+(position_of_my_main.y-y)*(position_of_my_main.y-y)+(position_of_my_main.z-z)*(position_of_my_main.z-z)); //position_of_my_main.x
        }
        edge_number--;
        sum+=index_sum;
    }
    sum=sum/2;//because i add every weight twice
    sum=sum/(edge_number/2);
    return sum;
}

double MeshGraph::AverageEdgePerVertex() const
{
    // TODO:
    int number_f_vertices=vertices.size();
    double edge_number=0;
    for(int i=0;i<number_f_vertices;i++)
    {

        std::list<Vertex*> temp=adjList[i];
        std::list<Vertex*>::const_iterator a = temp.begin();
        for (; a != temp.end(); a++)
        {
            edge_number++;
        }
        edge_number--;
    }
    double size=vertices.size();
    double result=edge_number/size;
    return result/2; //because I count every edge twice
}

int MeshGraph::TotalVertexCount() const
{
    // TODO:
    return vertices.size();
}

int MeshGraph::TotalEdgeCount() const
{
    // TODO:
    int edge_size=0;
    int vertex_size=vertices.size();
    for (int i=0;i<vertex_size;i++)
    {
        int e=adjList[i].size()-1;
        edge_size+=e;
    }
    return edge_size/2;
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    // TODO:
    int edge_number=0;

    //Vertex temp=vertices[vertexId];
    if(vertexId<0 || vertexId>=vertices.size())
    {
        return -1;
    }
    std::list<Vertex*> temp=adjList[vertexId];
    std::list<Vertex*>::const_iterator a = temp.begin();
    for (; a != temp.end(); a++)
    {
        edge_number++;
    }
    edge_number--;

    return edge_number;

}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds, int vertexId) const
{
    // TODO:

    if(vertexId<0 || vertexId>=vertices.size())
    {
        return;
    }
    std::list<Vertex*> temp=adjList[vertexId];
    std::list<Vertex*>::const_iterator a = temp.begin();
    a++; //to not push the vertex itself
    for (; a != temp.end(); a++)
    {
        outVertexIds.push_back((*a)->id);
    }
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex, int vertexIdFrom, int vertexIdTo, const Color& color) const
{
    // TODO:

    int number_of_vertices=vertices.size();
    bool flag_for_not_valid_id=false;

    //graph not having either vertexIdFrom or vertexIdTo, this function should return empty outputColorAllVertex.
    if((vertexIdFrom<0 || vertexIdFrom>=number_of_vertices) || (vertexIdTo<0 || vertexIdTo>=number_of_vertices))
    {
        flag_for_not_valid_id=true;
    }


    if(!flag_for_not_valid_id)
    {
        BinaryHeap min_heap= BinaryHeap();
        std::vector<double> distances; //weight
        std::vector<int> incoming_nodes; //previous node
        std::vector<bool> Visited; //visited true/false
        std::vector<int> shortest; //

        Visited.resize(number_of_vertices);
        outputColorAllVertex.resize(number_of_vertices);
        incoming_nodes.resize(number_of_vertices);
        for (int i=0;i<number_of_vertices;i++)
        {
            outputColorAllVertex[i].r=0;
            outputColorAllVertex[i].g=0;
            outputColorAllVertex[i].b=0;
        }
        for (int i=0; i< number_of_vertices;i++)
        {
            //create heapNode for all the vertices
            bool flag_add=min_heap.Add(i,FLT_MAX);
            incoming_nodes[i]=vertices[i].id;
            distances.push_back(FLT_MAX);
            Visited[i]=false;
        }

        //decrease the distance for the first index
        min_heap.ChangePriority(vertexIdFrom,0);
        distances[vertexIdFrom]=0;

        int UniqueId;
        double outweight;

        std::list<Vertex*> list;
        std::list<Vertex*>::const_iterator a ;
        while(min_heap.HeapSize()>0 )
        {
            bool pop=min_heap.PopHeap(UniqueId,outweight);
            Visited[UniqueId]=true;
            list = adjList[UniqueId];
            a= list.begin();
            a++;
            for (; a != list.end(); a++)
            {
                //benim list'im edge değil vertex tutuyor. o yüzden a'nın id'sı benim destination dediğim şey

                int destination=(*a)->id;
                if(Visited[destination]==false)
                {
                    double v_distance=outweight;

                    double x1=vertices[UniqueId].position3D.x;
                    double y1=vertices[UniqueId].position3D.y;
                    double z1=vertices[UniqueId].position3D.z;

                    double xs= pow(x1-(*a)->position3D.x,2);
                    double ys= pow(y1-(*a)->position3D.y,2);
                    double zs= pow(z1-(*a)->position3D.z,2);

                    double edge_weight= sqrt(xs+ys+zs);
                    double new_key= v_distance+edge_weight;

                    double current_key=distances[destination];
                    if(current_key>new_key)
                    {
                        min_heap.ChangePriority(destination,new_key);
                        distances[destination]=new_key;
                        incoming_nodes[destination]=UniqueId;
                    }
                }
            }
        }

        int index=vertexIdTo;
        while(index!=vertexIdFrom)
        {
            shortest.push_back(index);
            index=incoming_nodes[index];
        }
        shortest.push_back(index); //pushing the vertexidfrom

        int i=0;
        for (i=0;i<shortest.size(); i++ )
        {
            outputColorAllVertex[shortest[i]].r=color.r;
            outputColorAllVertex[shortest[i]].g=color.g;
            outputColorAllVertex[shortest[i]].b=color.b;
        }

    }

}

void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,int vertexId, const Color& color,
                                     int maxDepth, FilterType type,double alpha) const
{
    // TODO:
    int number_of_vertices=vertices.size();
    bool flag_for_not_valid_id=false;
    outputColorAllVertex.resize(number_of_vertices);
    //graph not having either vertexIdFrom or vertexIdTo, this function should return empty outputColorAllVertex.
    if(vertexId<0 || vertexId>=number_of_vertices)
    {
        flag_for_not_valid_id=true;
    }
    for(int i=0;i<number_of_vertices;i++)
    {
        outputColorAllVertex[i].r=0;
        outputColorAllVertex[i].g=0;
        outputColorAllVertex[i].b=0;
    }

        BinaryHeap min_heap=BinaryHeap();
        std::vector<bool> visited;
        std::vector<double> dist;
        std::vector<double> depth_index;
        std::list<Vertex*> list;
        std::list<Vertex*>::const_iterator a ;
        double filter=0;

        int dep;
        int heap=0;
        dist.resize(number_of_vertices);
        visited.resize(number_of_vertices);
        min_heap.Add(vertexId,(double)heap);
        depth_index.resize(number_of_vertices);
        outputColorAllVertex.resize(number_of_vertices);
        for (int i=0;i<vertices.size();i++)
        {
            visited[i]=false;
            dist[i]=FLT_MAX;
            depth_index[i]=FLT_MAX;
            outputColorAllVertex[i].r=0;
            outputColorAllVertex[i].g=0;
            outputColorAllVertex[i].b=0;
        }
        if ( type ==  FILTER_GAUSSIAN )
        {

            outputColorAllVertex[vertexId].r = exp(-(0*0)/(pow(alpha,2)))*color.r;
            outputColorAllVertex[vertexId].g = exp(-(0*0)/(pow(alpha,2)))*color.g;
            outputColorAllVertex[vertexId].b = exp(-(0*0)/(pow(alpha,2)))*color.b;
        }
        else if( type == FILTER_BOX)
        {
            if (filter<=alpha  )
            {
                outputColorAllVertex[vertexId]= color;
            }
        }
        visited[vertexId]=true;
        dist[vertexId]=0;
        depth_index[vertexId]=0;
        dep=0;
        int pop_id;
        double pop_weight;
        while(min_heap.HeapSize())
        {
            min_heap.PopHeap(pop_id, pop_weight);
            dep=depth_index[pop_id];
            dep++;
            list=adjList[pop_id];
            a=list.begin();
            for(; a != adjList[pop_id].end(); a++)
            {
                heap++;
                if (dep>maxDepth){
                    break;
                }

                if(visited[(*a)->id]== false)
                {

                    min_heap.Add(vertices[(*a)->id].id,heap);
                    visited[vertices[(*a)->id].id] = true;
                    depth_index[(*a)->id] = dep;
                    filter= Double3::Distance((*a)->position3D, vertices[pop_id].position3D)+dist[pop_id];
                    dist[(*a)->id] = filter;

                    if( type ==  FILTER_GAUSSIAN )
                    {
                        outputColorAllVertex[(*a)->id].r = exp(-(pow(filter,2))/(pow(alpha,2)))*color.r;
                        outputColorAllVertex[(*a)->id].g = exp(-(pow(filter,2))/(pow(alpha,2)))*color.g;
                        outputColorAllVertex[(*a)->id].b = exp(-(pow(filter,2))/(pow(alpha,2)))*color.b;
                    }

                }
                else if ( type == FILTER_BOX && filter<=alpha)
                {
                    outputColorAllVertex[(*a)->id]= color;
                }
            }
        dep = depth_index[pop_id];
        }


}


void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,int vertexId, const Color& color,int maxDepth, FilterType type,double alpha) const
{
    // TODO:
    int number_of_vertices=vertices.size();
    bool flag_for_not_valid_id=false;
    outputColorAllVertex.resize(number_of_vertices);
    if(vertexId<0 || vertexId>=number_of_vertices)
    {
        flag_for_not_valid_id=true;
    }
    for(int i=0;i<number_of_vertices;i++)
    {
        outputColorAllVertex[i].r=(unsigned char)0;
        outputColorAllVertex[i].g=(unsigned char)0;
        outputColorAllVertex[i].b=(unsigned char)0;
    }

    if(!flag_for_not_valid_id)
    {
        BinaryHeap min_heap=BinaryHeap();
        std::vector<bool> visited;
        std::vector<double> filter_parameters;
        std::list<Vertex*> list;
        std::list<Vertex*>::const_iterator a ;
        std::list<Vertex*>::const_iterator b ;
        std::vector<double> d;
        d.resize(number_of_vertices);
        visited.resize(number_of_vertices);
        outputColorAllVertex.resize(number_of_vertices);
        min_heap.Add(vertexId,(double)vertexId);

        for (int i=0;i<vertices.size();i++)
        {
            visited[i]=false;
            d[i]=FLT_MAX;
        }
        visited[vertexId]=true;
        d[vertexId]=0;

        if(maxDepth!=0)
        {
            int depth=0;
            int pop_id;
            double  pop_weight;

            while (min_heap.HeapSize()>0) {
                bool flag=min_heap.PopHeap(pop_id,pop_weight);
                visited[pop_id]=true;
                depth = d[pop_id];
                list=adjList[pop_id];
                a=list.begin();
                b=list.begin();
                a++;
                b++;

                for (; b!=list.end();b++)
                {
                    d[(*b)->id]=depth+1;

                }
                for (; a!=list.end();a++)
                {
                    if(visited[(*a)->id]==false)
                    {
                        if(d[(*a)->id]<maxDepth)
                        {
                            bool flag_2=min_heap.Add((*a)->id,(*a)->id);
                        }
                        //incoming_nodes[(*a)->id]=pop_id; //[(*a)->id]=pop_id;
                        visited[(*a)->id]=true;
                    }
                }
            }
        }

        double filter_parameter;

        for(int j=0;j<number_of_vertices;j++)
        {
            if(visited[j]==true)
            {
                double x_dest=vertices[vertexId].position3D.x;
                double y_dest=vertices[vertexId].position3D.y;
                double z_dest=vertices[vertexId].position3D.z;
                double x_source=vertices[j].position3D.x;
                double y_source=vertices[j].position3D.y;
                double z_source=vertices[j].position3D.z;
                filter_parameter= sqrt(pow(x_source-x_dest,2)+pow(y_source-y_dest,2)+pow(z_source-z_dest,2));
                
                if(type==FILTER_GAUSSIAN)
                {
                    double power= pow(filter_parameter,2)/pow(alpha,2);
                    filter_parameter= 1/exp(power);
                }


                else if(type==FILTER_BOX)
                {
                    if(filter_parameter<=alpha  && filter_parameter>=(-alpha))
                    {
                        filter_parameter=1;
                    }
                    else
                    {
                        filter_parameter=0;
                    }
                }

                outputColorAllVertex[j].r=(filter_parameter*(double)color.r);
                outputColorAllVertex[j].g=(filter_parameter*(double)color.g);
                outputColorAllVertex[j].b=(filter_parameter*(double)color.b);
               

            }
        }

    }
}

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,const std::string& fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    // IMPLEMENTED
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}
