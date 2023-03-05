# this file is to select only events with one anti tau (id = -13) from LHE file

# Open the input and output file
with open("input.lhe", "r") as in_file, open("output.lhe", "w") as out_file:
    # Initialize variables to store the current event and the number of tau particles
    current_event = []
    num_taus = 0
    
    # Iterate over each line in the input file
    for line in in_file:
        # If the line marks the start of a new event, check the number of tau particles in the previous event
        if line.startswith(" - - - - - -"):
            # If the previous event had more than one tau particle, skip it
            if num_taus > 1:
                current_event = []
            # Otherwise, write the previous event to the output file
            else:
                for event_line in current_event:
                    out_file.write(event_line)
            # Reset the current event and number of tau particles
            current_event = [line]
            num_taus = 0
        # If the line contains particle information, check if it's a tau particle
        elif line[0].startswith("-"):
            particle_id = int(line.split()[0])
            if particle_id == -13:
                num_taus += 1
        # Add the line to the current event
        current_event.append(line)
    # Write the last event to the output file
    if num_taus <= 1:
        for event_line in current_event:
            out_file.write(event_line)
