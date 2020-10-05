#!/bin/zsh
export PATH="/Users/trevorrees/Documents/sonarscanner/sonar-scanner-4.4.0.2170-macosx/bin:$PATH"
export PATH="/Users/trevorrees/Documents/sonarscanner/build-wrapper-macosx-x86:$PATH"
export SONAR_TOKEN="2dbb9fa6053adecd3aef267e3bbf2bb8730b42e1"

build-wrapper-macosx-x86 --out-dir bw-output g++ -std=c++11 main.cpp scheduler.cpp task.cpp simpleTask.cpp -o scheduler

sonar-scanner \
  -Dsonar.organization=tjrees \
  -Dsonar.projectKey=tjrees_CIS566_scheduled_task_demo \
  -Dsonar.sources=. \
  -Dsonar.cfamily.build-wrapper-output=bw-output \
  -Dsonar.host.url=https://sonarcloud.io
