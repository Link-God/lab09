cmake_minimum_required(VERSION 3.0) #Версия cmake

set(CMAKE_CXX_STANDARD 11) # стандарт с++
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" OFF) # выключаем опцию необходимую для создания примеров(?) 

project(print) # имя проекта

add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp) # добавляем библиотеку (статическую ) из указаного пути 

target_include_directories(print PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
# выше указываем каталоги для коспиляции . Public указывает на то что мы используем эти заголовки в общедоступных файлах и то что они могут быть включены в другой кдиент(?) print

if(BUILD_EXAMPLES)
  file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp") # будет хранить в переменной все файлы удовлетворяющие условию 
  foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES}) #команды для каждого значения в списке
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE) #получаем компонент из списка
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE}) #добавляем исполняемый файл из источника
    target_link_libraries(${EXAMPLE_NAME} print) #добавление библиотек для цели
    install(TARGETS ${EXAMPLE_NAME}
      RUNTIME DESTINATION bin
    ) # указывает правли для запуска во время установки 
  endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()

install(TARGETS print
    EXPORT print-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
#  правила для запуска во время установки
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
install(EXPORT print-config DESTINATION cmake)
