#!/usr/bin/env groovy
pipeline {
    agent any
    stages {
        stage('Git Checkout') {
            steps {
                script {
                    git branch: 'main',
                        credentialsId: 'token',
                        url: 'https://github.com/junwoosan/JTEKT-demo.git'
                }
            }
        }

        stage('REST API script execution'){
            steps {
        
                echo 'hello junwoo'
                powershell 'ls'
                powershell 'pwd'
                powershell 'whoami'
                powershell 'python pipeline_B2B.py /tmp/ep/JTEKT-demo  test.slx'
      
            }
        }
    }
}

