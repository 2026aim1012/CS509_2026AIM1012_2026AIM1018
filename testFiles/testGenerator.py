import random
import os
import math

def generate_bellman_ford_test(filename, V, E, has_negative_cycle=False):
    edges = set()
    adj = {i: [] for i in range(V)}
    
    for i in range(1, V):
        edges.add((0, i))
        adj[0].append((i, random.randint(1, 10)))
        
    while len(edges) < E:
        u = random.randint(0, V - 1)
        v = random.randint(0, V - 1)
        if u != v and (u, v) not in edges:
            weight = random.randint(-1, 15) 
            edges.add((u, v))
            adj[u].append((v, weight))

    with open(filename, 'w') as f:
        f.write(f"{V} {len(edges)}\n")
        for u in range(V):
            line = f"{u} {len(adj[u])}"
            for v, w in adj[u]:
                line += f" {v} {w}"
            f.write(line + "\n")
        f.write("SOURCE 0\n")
    print(f"Generated {filename}")

def generate_floyd_warshall_test(filename, V, density=0.4):
    matrix = [["INF" for _ in range(V)] for _ in range(V)]
    for i in range(V):
        matrix[i][i] = 0
        for j in range(V):
            if i != j and random.random() < density:
                matrix[i][j] = random.randint(-1, 15)
                
    with open(filename, 'w') as f:
        f.write(f"{V}\n")
        for row in matrix:
            f.write(" ".join(str(val) for val in row) + "\n")
    print(f"Generated {filename}")

def generate_undirected_unweighted_test(filename, V, E):
    edges = set()
    adj = {i: [] for i in range(V)}
    
    while len(edges) < E:
        u = random.randint(0, V - 1)
        v = random.randint(0, V - 1)
        if u != v and tuple(sorted((u, v))) not in edges:
            edges.add(tuple(sorted((u, v))))
            adj[u].append(v)
            adj[v].append(u)

    with open(filename, 'w') as f:
        f.write(f"{V} {len(edges)}\n")
        for u in range(V):
            line = f"{u} {len(adj[u])}"
            for v in sorted(adj[u]):  # Sorted for Triangle Counting optimization
                line += f" {v}"
            f.write(line + "\n")
    print(f"Generated {filename}")

def generate_kmeans_test(filename, N, D, K, max_iter=300, tol=0.0001):
    # Generates points in distinct clusters to create a solvable K-Means problem
    with open(filename, 'w') as f:
        f.write(f"{N} {D} {K}\n")
        centers = [[random.uniform(0, 100) for _ in range(D)] for _ in range(K)]
        
        for _ in range(N):
            cluster = random.randint(0, K-1)
            point = [centers[cluster][d] + random.uniform(-5, 5) for d in range(D)]
            f.write(" ".join(f"{val:.4f}" for val in point) + "\n")
            
        f.write(f"MAX_ITERATIONS {max_iter}\n")
        f.write(f"TOLERANCE {tol}\n")
    print(f"Generated {filename}")

def generate_fastmap_test(filename, N, k):
    print(f"Starting generation of {filename} (N={N}). This may take a minute or two for large N...")
    
    # Generate the base points (only N objects, takes barely any memory)
    points = [[random.uniform(0, 50) for _ in range(5)] for _ in range(N)] 
    
    with open(filename, 'w') as f:
        f.write(f"{N} {k}\n")
        
        # Calculate and write row-by-row to prevent memory overload
        for i in range(N):
            row = []
            for j in range(N):
                if i == j:
                    row.append("0.0000")
                else:
                    # Calculate distance on the fly
                    dist = math.sqrt(sum((points[i][d] - points[j][d])**2 for d in range(5)))
                    row.append(f"{dist:.4f}")
            
            # Write the single row to disk immediately
            f.write(" ".join(row) + "\n")
            
            # Print a progress update every 1000 rows
            if (i + 1) % 1000 == 0:
                print(f"  ... processed {i + 1} / {N} rows")
                
    print(f"Successfully generated {filename}!")

if __name__ == "__main__":
    # Updated to save directly into 'testFiles' folder
    os.makedirs("testFiles", exist_ok=True)
    os.chdir("testFiles")
    
    print("--- Generating Bellman-Ford Tests ---")
    bf_sizes = [(10, 30), (100, 300), (10000, 30000), (50000, 150000), (100000, 300000)] 
    for v, e in bf_sizes:
        generate_bellman_ford_test(f"bf_{v}.txt", v, e)
        
    print("\n--- Generating Floyd-Warshall Tests ---")
    fw_sizes = [10, 100, 500, 1000, 2000] 
    for v in fw_sizes:
        generate_floyd_warshall_test(f"fw_{v}.txt", v)
        
    print("\n--- Generating Triangle Counting & Connected Components Tests ---")
    tc_cc_sizes = [(10, 30), (100, 300), (10000, 30000), (50000, 150000), (100000, 300000)]
    for v, e in tc_cc_sizes:
        generate_undirected_unweighted_test(f"tc_{v}.txt", v, e)
        generate_undirected_unweighted_test(f"cc_{v}.txt", v, e)

    print("\n--- Generating Betweenness Centrality Tests ---")
    bc_sizes = [(10, 30), (100, 300), (1000, 3000), (5000, 15000), (10000, 30000)]
    for v, e in bc_sizes:
        generate_undirected_unweighted_test(f"bc_{v}.txt", v, e)

    print("\n--- Generating K-Means Tests ---")
    # Dataset specs: (Name, N, D, K)[cite: 8]
    km_specs = [("km_01.txt", 100, 2, 3), ("km_02.txt", 1000, 2, 5), 
                ("km_03.txt", 10000, 5, 8), ("km_04.txt", 100000, 5, 10)]
    for name, n, d, k in km_specs:
        generate_kmeans_test(name, n, d, k)
        
    print("\n--- Generating FastMap Tests ---")
    # Dataset specs: (Name, N, k)[cite: 8]
    fm_specs = [("fm_01.txt", 10, 2), ("fm_02.txt", 100, 2), 
                ("fm_03.txt", 1000, 3), ("fm_04.txt", 10000, 3)]
    for name, n, k_target in fm_specs:
        generate_fastmap_test(name, n, k_target)
        
    print("\nAll test files generated successfully in the 'testFiles' folder!")