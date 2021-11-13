/**
 * @file node.h
 * @author Rutvik Kevadiya (rutvik08@umd.edu) Darshan Jain (djain12@umd.edu) Param Dave (pdave1@umd.edu)
 * @brief This file contains a class to represent a node in a maze.
 * @version 0.1
 * @date 2021-11-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef NODE_H
#define NODE_H

#include <array>

namespace rwa2 {
    /**
     * @brief Class to represent a node (cell) in a maze.
     *
     *A node is just a space delimited by 4 walls
     *
     */
    class Node
    {
    public:
        Node() {
            for (int i = 0; i < 4; i += 1) {
                m_walls[i] = false;
            }
        }
        /**
         * @brief Set the wall of a cell
         *
         * @param direction NORTH, EAST, SOUTH, or WEST
         * @param is_wall true if there is a wall, otherwise false
         */
        void set_wall(int direction, bool is_wall);
        /**
         * @brief Return whether or not there is a wall in a cell
         *
         * @param direction Direction to set for wall (NORTH, EAST, SOUTH, or WEST)
         * @return true There is a wall in the given direction in the cell
         * @return false There is no wall in the given direction in the cell
         */
        bool is_wall(int direction) const;
        /**
         * @brief Compute the number of walls surrounding a node
         * 
         * @return int Number of walls surrounding a node
         */
        int compute_number_of_walls() const;
        /**
         * @brief Get the x coordinate in the node
         * 
         * @return int 
         */
        int get_x();
        /**
         * @brief Set the x coordinate in the node
         * 
         * @param X 
         */
        void set_x(int X);
        /**
         * @brief Get the y coordinate in the node
         * 
         * @return int 
         */
        int get_y();
        /**
         * @brief Set the y coordinate in the node
         * 
         * @param Y 
         */
        void set_y(int Y);

        /**
         * @brief compares the values of the nodes
         * 
         * @param n 
         * @return true - If all the values are equal
         * @return false - If any one value is not equal
         */
        bool operator==(rwa2::Node n);

        /**
         * @brief Sets the value of the node 
         * 
         * @param n - The node whose value has to be set
         */
        void operator=(rwa2::Node n);
        /**
         * @brief Get the mwalls object - Returns a array of 4 elements containing the information about walls surrounding the node
         * 
         * @return std::array<bool, 4> 
         */
        std::array<bool, 4> get_mwalls();

    private:
        std::array<bool, 4> m_walls; //all four walls in a cell
        int x;
        int y;
    };
}
#endif
