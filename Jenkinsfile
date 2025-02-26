#!/usr/bin/env groovy
pipeline {
    agent any
    stages {
        stage('Git Checkout') {
            steps {
                script {
                    git branch: 'main',
                        credentialsId: 'token',
                        url: 'https://github.com/yangz9842/Jtekt.git'
                }
            }
        }

        stage('REST API script execution') {
            steps {
                echo 'hello yang12345'

                // Replace PowerShell commands with bash commands
                sh 'ls'                // Equivalent to PowerShell "ls"
                sh 'pwd'               // Equivalent to PowerShell "pwd"
                sh 'whoami'            // Equivalent to PowerShell "whoami"
                
                // Run your Python script with arguments
                sh 'python3 pipeline_B2B.py /tmp/ep/ test.slx'
            }
        }
    }
}


