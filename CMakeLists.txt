cmake_minimum_required(VERSION 3.0.2)
project(ros_turtle)

## Catkin과 필요한 패키지를 찾는 부분
find_package(catkin REQUIRED COMPONENTS
  roscpp           # C++에서 ROS 기능을 사용할 수 있도록 하는 패키지
  std_msgs         # 표준 메시지 타입을 사용하기 위한 패키지
  geometry_msgs    # 기하학적 메시지 타입을 사용하기 위한 패키지
  turtlesim        # Turtlesim 노드와 관련된 기능을 사용하기 위한 패키지
)

## Catkin 패키지 선언
catkin_package()

## 헤더 파일의 추가 위치를 지정 (include 디렉토리)
include_directories(
  ${catkin_INCLUDE_DIRS}  # Catkin 패키지들이 제공하는 헤더 파일을 포함
)

## 실행 파일을 추가하고 연결할 라이브러리 지정
add_executable(c_publisher src/1/c_publisher.cpp)   # 1번 문제 C 스타일 파일 추가
add_executable(oop_publisher src/1/oop_publisher.cpp) # 1번 문제 OOP 스타일 파일 추가

add_executable(c_circle src/2/c_circle.cpp)   # 2번 문제 C 스타일 파일 추가
add_executable(oop_circle src/2/oop_circle.cpp) # 2번 문제 OOP 스타일 파일 추가

add_executable(c_stop src/3/c_stop.cpp)   # 3번 문제 C 스타일 파일 추가
add_executable(oop_stop src/3/oop_stop.cpp) # 3번 문제 OOP 스타일 파일 추가

add_executable(c_square src/4/c_square.cpp)   # 4번 문제 C 스타일 파일 추가
add_executable(oop_square src/4/oop_square.cpp) # 4번 문제 OOP 스타일 파일 추가

# **중복된 타겟 이름을 수정하여 고유한 이름으로 변경**
add_executable(c_mode src/5/c_mode.cpp)       # 5번 문제 C 스타일 파일 추가
add_executable(oop_mode src/5/oop_mode.cpp)   # 5번 문제 OOP 스타일 파일 추가

## 실행 파일과 Catkin 라이브러리를 연결
target_link_libraries(c_publisher ${catkin_LIBRARIES})   # c_publisher 노드를 catkin 라이브러리와 연결
target_link_libraries(oop_publisher ${catkin_LIBRARIES}) # oop_publisher 노드를 catkin 라이브러리와 연결
target_link_libraries(c_circle ${catkin_LIBRARIES})      # c_circle 노드를 catkin 라이브러리와 연결
target_link_libraries(oop_circle ${catkin_LIBRARIES})    # oop_circle 노드를 catkin 라이브러리와 연결
target_link_libraries(c_stop ${catkin_LIBRARIES})        # c_stop 노드를 catkin 라이브러리와 연결
target_link_libraries(oop_stop ${catkin_LIBRARIES})      # oop_stop 노드를 catkin 라이브러리와 연결
target_link_libraries(c_square ${catkin_LIBRARIES})      # c_square 노드를 catkin 라이브러리와 연결
target_link_libraries(oop_square ${catkin_LIBRARIES})    # oop_square 노드를 catkin 라이브러리와 연결

# **새로운 타겟을 연결**
target_link_libraries(c_mode ${catkin_LIBRARIES})        # c_mode 노드를 catkin 라이브러리와 연결
target_link_libraries(oop_mode ${catkin_LIBRARIES})      # oop_mode 노드를 catkin 라이브러리와 연결
