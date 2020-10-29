// Copyright 2020 HASSAN EZZALDEEN

#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "./most_different_vector_elements.h"

TEST(most_different_vector_elements, can_find_the_right_answer) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> v(5);

  if (rank == 0) {
    v = getRandVect(5);
    }

  double res = mpi_find(v);

  if (rank == 0) {
    ASSERT_EQ(single_find(v), res);
  }
}

TEST(most_different_vector_elements, can_find_the_right_answer_with_small_vector) {
  int rank;
  std::vector<int> v(3);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    v = getRandVect(3);
  }

  double res = mpi_find(v);

  if (rank == 0) {
    ASSERT_EQ(single_find(v), res);
  }
}

TEST(most_different_vector_elements, can_find_the_right_answer_with_big_vector) {
  std::vector<int> v(100);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    v = getRandVect(100);
  }

  double res = mpi_find(v);

  if (rank == 0) {
    ASSERT_EQ(single_find(v), res);
  }
}

TEST(most_different_vector_elements, can_find_the_answer_with_very_big_vector) {
  std::vector<int> v(1000);
  int rank;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    v = getRandVect(1000);
  }

  double res = mpi_find(v);

  if (rank == 0) {
    ASSERT_EQ(single_find(v), res);
  }
}

TEST(most_different_vector_elements, can_find_the_right_answer_with_even_number_elements_vector) {
  std::vector<int> v(7);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    v = getRandVect(7);
  }

  double res = mpi_find(v);

  if (rank == 0) {
    ASSERT_EQ(single_find(v), res);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
    ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
