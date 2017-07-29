import React from 'react';
import PropTypes from 'prop-types';
import CenteredLayout from '../../components/CenteredLayout/CenteredLayout';
import Background from '../../components/Background/Background';
import Header from '../../components/Header/Header';

export const Tasks = () => (
	<Background>
		<Header/>
		<CenteredLayout>
			Tasks
		</CenteredLayout>
	</Background>
);



export default Tasks;
