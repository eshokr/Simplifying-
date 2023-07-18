
"""
This file is used to get a file from ssh directly to local directory by passing the remote file path as an argument
example:
python getSSHFile.py \afs\..\..\..\..\test.root
"""

import paramiko
import getpass
import sys
import os

# SSH connection details
hostname = 'lxplus.cern.ch'
port = 22
username = 'WriteYourUserName'


# Check if the remote_file_path argument is provided
if len(sys.argv) < 2:
    print("Usage: python a.py remote_file_path")
    sys.exit(1)

# Prompt the user for the password
password = getpass.getpass("Enter your password: ")

# Get the remote file path from the command-line argument
remote_file_path = sys.argv[1]

# Extract the filename from the remote file path
filename = os.path.basename(remote_file_path)

# Local file path
local_file_path = os.path.join(os.getcwd(), filename)

# Create SSH client
client = paramiko.SSHClient()
client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

try:
    # Connect to SSH server
    client.connect(hostname, port, username, password)

    # Open SFTP session
    sftp = client.open_sftp()

    # Download file
    sftp.get(remote_file_path, local_file_path)

    print(f"File downloaded successfully: {local_file_path}")

finally:
    # Close SSH client
    client.close()
