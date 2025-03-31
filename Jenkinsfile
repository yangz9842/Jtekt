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
                sh 'ls -l /tmp/ep'                // Equivalent to PowerShell "ls"
                sh 'pwd'               // Equivalent to PowerShell "pwd"
                sh 'whoami'            // Equivalent to PowerShell "whoami"
                // Run your Python script with arguments
                sh 'python3 pipeline_B2B_1.py /tmp/ep/ powerwindow_tl.slx'
                
            }
            
        }
        stage('Publish Report') {
            steps {
                // Publish the HTML report
                publishHTML([
                    reportDir: 'C:/ProgramData/Jenkins/.jenkins/workspace/jtekt_JP//B2B_reports',
                    reportFiles: 'B2B_report_for_powerwindow_tl.slx.html',
                    reportName: 'BTC Test Report',
                     keepAll: true,                 // Keeps all historical reports
                     alwaysLinkToLastBuild: true,   // Links always point to the latest build
                     allowMissing: false            // Fails if the report is missing (set to true to avoid failure)
                ])
            }
        }
    }
    
}


