import numpy as np
from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator

# Librerías y variables iniciales
n = 10 ** 3
qubit_index = 0
backend = AerSimulator()
message = [QuantumCircuit(1, 2) for _ in range(n)]

ataque = input("Introduce 's' para simular un ataque de Eve(si no introduce nada no se simula el ataque): ").strip().lower()

# Preparación de estados (Alice)
alice_bits = np.random.randint(2, size=n)
alice_bases = np.random.randint(2, size=n)

for i, qc in enumerate(message):
    if alice_bits[i] == 1:
        qc.x(0)
    if alice_bases[i] == 1:
        qc.h(0)
        
if ataque == 's':
    # ATAQUE DE EVE
    eve_bases = np.random.randint(2, size=n)
    classical_bit_index_for_eve = 1 

    for i, qc in enumerate(message):
        if eve_bases[i] == 1:
            qc.h(0)
    
        qc.measure(qubit_index, classical_bit_index_for_eve)
    
        if eve_bases[i] == 1:
            qc.h(0)

# Cambio de bases (Bob)
bob_bases = np.random.randint(2, size=n)

for i, qc in enumerate(message):
    if bob_bases[i] == 1:
        qc.h(0)

# Medida
classical_bit_index_for_bob_measurement = 0

for qc in message:
    qc.measure(qubit_index, classical_bit_index_for_bob_measurement)

# Comparación de bases
cbit = classical_bit_index_for_bob_measurement
bob_measured_bits = []

for qc in message:
    transpiled_qc = transpile(qc, backend)
    result = backend.run(transpiled_qc, shots=1).result()
    counts = result.get_counts()
    measured_bit = list(counts.keys())[0][::-1][cbit]
    bob_measured_bits.append(measured_bit)

alice_key = []
bob_key = []

for i in range(n):
    if alice_bases[i] == bob_bases[i]:
        alice_key.append(int(alice_bits[i]))
        bob_key.append(int(bob_measured_bits[i]))

# Cálculo del QBER
errores = 0
for i in range(len(alice_key)):
    if alice_key[i] != bob_key[i]:
        errores += 1

qber = errores / len(alice_key) if len(alice_key) > 0 else 0

print(f"Longitud original (n): {n} bits")
print(f"Longitud de la clave final coincidente: {len(alice_key)} bits")
print(f"Número de errores detectados: {errores}")
print(f"Tasa de error cuántico (QBER): {qber}")
print("Si la tasa de error cuántico es 11 o superior, considere que haya un atacante presente en la comunicación.")